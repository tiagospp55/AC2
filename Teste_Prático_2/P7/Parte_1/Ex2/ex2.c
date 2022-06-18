#include <detpic32.h>

void _int_(VECTOR) isr_adc(void);

volatile unsigned char voltage = 0; // Global variable  ( salvaguardar que a variavel )
// voltage pode ser alterada na interrupção

int main(void){

    // Configure todos os portos (digitais, analógicos e o módulo A/D)
    TRISBbits.TRISB4 = 1;  // Desconectar a saida digital RB4
    AD1PCFGbits.PCFG4 = 0; // RB4 como entrada análogica
    AD1CON1bits.SSRC = 7;   // Conversão constante do trigger
    AD1CON1bits.CLRASAM = 1;  // Parar a conversão quando a primeira interrupção acontece

    // Configurar o sistema de interrupções
    AD1CON3bits.SAMC = 16; // O tempo de amsotragem é 16 TAD (TAD = 100ns)
    AD1CON2bit.SMPI = 7;   // Ao fim de 8 amostras (7+1)
    AD1CHSbits.CH0SA = 4;   
    AD1CON1bits.ON = 1;

    // Autorizar a interrupção do ADC
    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    AD1CON1bits.ASAM = 1; 

    unsigned int cnt = 0;

    while(1){
        if (cnt %25 == 0)   // 250 ms (4 samples/second)
            AD1CON1bits = 1; // start conversation A/D
        send2display(voltage);

        cnt++;
        delay(10);
    };

    return 0;
}

void _int_(27) isr_adc(void){
    
    int *p = (int *) &ADC1BUF0;
    int i, average = 0;

    for (i = 0; i < 8; i++)   // Calculate buffer average (8 samples)
        average += p[i * 4];

    voltage = toBcd(voltageConversion(average / 8));  // Convert voltage amplitude to decimal 
    
    IFS1bits.AD1IF = 0;  // Reset AD1IF flag

}



void send2displays(char value)
{
    static const char display7Scodes[] = {
                                        0x3F, //0
                                        0x06, //1
                                        0x5B, //2
                                        0x4F, //3
                                        0x66, //4
                                        0x6D, //5
                                        0x7D, //6
                                        0x07, //7
                                        0x7F, //8
                                        0x6F, //9
                                        0x77, //A
                                        0x7C, //b
                                        0x39, //C
                                        0x5E, //d
                                        0x79, //E
                                        0x71  //F
                                        };

    static int displayFlag = 0;

    unsigned char dh = value >> 4;      // Get the index of the decimal part
    unsigned char dl = value & 0x0F;    // Get the index of the unitary part
    
    // Get the correct hex code for the number
    dh = display7Scodes[dh];
    dl = display7Scodes[dl];
    
    if (displayFlag == 0)
    {
        LATD = (LATD | 0x0040) & 0xFFDF;    // Dipslay High active and Display Low OFF
        LATB = (LATB & 0x80FF) | ((unsigned int)(dh)) << 8; // Clean the display and set the right value
    } else {
        LATD = (LATD | 0x0020) & 0xFFBF;    // Display High OFF and Display High active
        LATB = (LATB & 0x80FF) | ((unsigned int)(dl)) << 8; // Clean the display and set the right value
    }

    displayFlag = !displayFlag;
}


int voltageConversion(int VAL_AD)
{
    return (VAL_AD * 33 + 511) / 1023;
    //return (VAL_AD * 3.3 ) / 1023*10;  
}

int toBcd(int value)
{
    return ((value/10) << 4) + (value % 10);
}

void delay(int ms)
{
    for (; ms > 0; ms--)
    {
        resetCoreTimer();
        while (readCoreTimer() < 20000);
    }
}
    // Ativar o bit AD1IF do registo IFS1 é gerar um pedido de interrupção

    // 1. Configurar o nivel de prioridade das interrupções geradas pelo módulo A/D 
    // registo IPC6, nos 3 bits AD1IP; terá que ser escrito um valor entre 1 e 6;
    // O valor 7, a que corresponde a prioridade máxima, não deve ser usado; Para o valor 0 os pedidos de interrupção 
    // nunca são aceites, o que equivale a desativar essa fonte de interrupção
    // Para configurar a prioridade temos que utilizar o código 
    //              IPC6bits.AD1IP = 2;  
    

    // 2. Fazer o reset de alguma interrupção pendente - registo IFS1, bit AD1IF
    //              IFS1bits.AD1IF = 0;

    // 3. Autorizar as interrupções geradas pelo módulo A/D - registo IEC1, bit AD1IE
    //              IEC1bits.AD1

    // Ativar globalmente o sistema de interrupções
    //              Enable Interrupts(); /Defined on detpic.h

    // Interrupt service routine (interrupt handler) //Replace VECTOR by the A/D vector
                                                    // number - see "PIC32 family datasheet"
        //{
                //ISR actions
                //(..)
                //IFS1bits.AD1IF = 0;   // Reset AD1IF flag
        //}

    // O prefixo "_int_" indica ao compilador que se trata de uma RSI

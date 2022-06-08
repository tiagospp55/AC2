#include <detpic32.h>

void _int_(VECTOR) isr_adc(void);

int main(void){

    // Configure todos os portos (digitais, analógicos e o módulo A/D)
    TRISBbits.TRISB4 = 1;  // Desconectar a saida digital RB4
    AD1PCFGbits.PCFG4 = 0; // RB4 como entrada análogica
    AD1CON1bits.SSRC = 7;   // Conversão constante do trigger
    AD1CON1bits.CLRASAM = 1;  // Parar a conversão quando a primeira interrupção acontece

    // Configurar o sistema de interrupções
    AD1CON3bits.SAMC = 16; // O tempo de amsotragem é 16 TAD (TAD = 100ns)
    AD1CON2bit.SMPI = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // Autorizar a interrupção do ADC
    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    AD1CON1bits.ASAM = 1;

    while(1){};

    return 0;
}

void _int_(27) isr_adc(void){
    printInt(ADC1BUF0, 16 | 3 << 16);  // print
    putChar('\n');
    AD1CON1bits.ASAM = 1;
    IFS1bits.AD1IF = 0;
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

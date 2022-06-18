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

    while(1){

    };

    return 0;
}

void _int_(27) isr_adc(void){
    LATDbits.LATD11 = 0;
    adc_value = ADC1BUF0;
    AD1CON1bit.ASAM = 1;
    LATDbits.LATD11 = 1;
    IFS1bits.AD1IF = 0;
    bIT1DOADCJLA=1;       // wccwvvwv
}
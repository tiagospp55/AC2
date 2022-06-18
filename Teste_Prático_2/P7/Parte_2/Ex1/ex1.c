#include <detpic32.h>

void _int_(VECTOR) isr_adc(void); 

volatile  int adc_value;
int main(void){

      // Configure todos os portos (digitais, analógicos e o módulo A/D)
    TRISBbits.TRISB4 = 1;  // Desconectar a saida digital RB4
    AD1PCFGbits.PCFG4 = 0; // RB4 como entrada análogica
    AD1CON1bits.SSRC = 7;   // Conversão constante do trigger
    AD1CON1bits.CLRASAM = 1;  // Parar a conversão quando a primeira interrupção acontece

    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = 0;       // Interrupt is generated after 1 sample
    AD1CHSbits.CH0SA = 4;       // analog channel input 4
    AD1CON1bits.ON = 1;         // Enable the A/d configuration sequence

    IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
    IFSC1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    AD1CON1bits.ASAM = 1; // Start Conversion
    resetCoreTimer();

    
    while(1);

    return 0;
}

void _int_(27) isr_adc(void){
    int time = readCoreTimer();
    LATDbits.LATD11 = 0;
    adc_value = ADC1BUF0;
    LATE = LATE | 0x0001;
    
    time *= 50;
    time -= 3600;
    printInt(time);
    putChar('\n');

    resetCoreTimer();
    AD1CON1bit.ASAM = 1;
    IFS1bits.AD1IF = 0;
}


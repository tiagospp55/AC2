#include <detpic32.h>

volatile int voltage = 0; // global variable
unsigned int VECTOR_TIMER1 = 4;
unsigned int VECTOR_TIMER3 = 12;
void configAll(void);
int toBCD(int value);
int convertionVoltage(int value);
void send2displays(char value);

int main(void){

    configAll();
    IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag
    IFS0bits.T1IF = 0; // Reset timer T2 interrupt flag

    EnableInterrupts();

    while(1);

    return 0;
}


int convertionVoltage(int value){ 
    return  ((value  * 33+ 511)/1023);
}

int toBCD(int value){
    return (((value/10) << 4) + (value % 10));
}

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;
    while(IFS1bits.AD1IF == 0); // Start the ADC

    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    send2displays(voltage);
     IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){
    int average, sum = 0;
    int *p = (int *)(&ADC1BUF0);
    int i = 0;
    for ( i = 0; i < 4; i++){
        sum = sum + p[i*4];
    }
    average = sum / 4;

    voltage = toBCD(convertionVoltage(average));

    IFS1bits.AD1IF = 0;  // Reset AD1IF flag
}

void configAll(void){
    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 4-1; // Interrupt is generated after XX samples
    // (replace XX by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence
    
    
    T1CONbits.TCKPS = 3;
    T3CONbits.TCKPS = 3;

    PR1 = 62499;
    PR3 = 49999;

    TMR1 = 0;
    TMR3 = 0;

    T1CONbits.TON = 1;
    T3CONbits.TON = 1;

    IPC1bits.T1IP = 1; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T2 interrupts
  

    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts

}


void send2displays(char value){

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

    unsigned char dh = value >> 4;
    unsigned char dl = value & 0x0F;


    dh = display7Scodes[dh];
    dl = display7Scodes[dl];

    unsigned int displayFlag = 0;

     if (displayFlag == 0)
    {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | ((unsigned int)(dh)) << 8; // Clean the display and set the right value
    } else {

        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | ((unsigned int)(dl)) << 8; // Clean the display and set the right value
    }

    displayFlag  != displayFlag;
}
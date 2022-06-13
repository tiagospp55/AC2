#include <detpic32.h> 

int main(void){

    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T2CONbits.TON = 1;

    OC1CONBits.OCM = 6;
    OC1CONbits.OCTSEL = 1;
    OC1RS = 10000;
    OC1CONbits.ON = 1;

    IPC3bits.T3IP = 3;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    EnableInterrupts();

    while(1);

}
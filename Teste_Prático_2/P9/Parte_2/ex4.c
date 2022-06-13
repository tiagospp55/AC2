#include <detpi32.h>

int main(void){


    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T2CONbits.TON = 1;

    OC1CONBits.OCM = 6;
    OC1CONbits.OCTSEL = 1;
    dutyCycle(25);
    OC1CONbits.ON = 1;

    IPC3bits.T3IP = 3;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    TRISDbits.TRISD0 = 1;  // ENTRADA
    TRISDbits.TRISD14 = 0; //SAIDA

    LATDbits.LATD14 = 0;
    
    
    whiel(1){
        LATDbits.LATD14 = PORTDbits.PORTD0;
    }
}

    void setPWM(unsigned int dutyCycle)
{
    if (dutyCycle >= 0 && dutyCycle <= 100)
        OC1RS = (dutyCycle * (PR3 + 1)) /100;
}

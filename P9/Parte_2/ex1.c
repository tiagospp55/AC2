#include <detpic32.h>

int main(void)
{
    // Timer3
    T2CON = 0;
    TMR2 = 0;

    T2CONbits.TCKPS = 5;        // 1:4 prescaler Fout_presc = 5Mhz;
    PR2 = 62499;                // Fout = 20Mhz / 4(49999+1) = 100Hz
    TMR2 = 0;                   // Reset timer T3 count register
    T2CONbits.TON = 1;          // Enable timer T3

    OC1CONbits.OCM = 6;         // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =0;       // Use timer T3 as the time base for PWM generation
    OC1RS = (20*(PR2 + 1) +50)/100;                // Ton constant
    OC1CONbits.ON = 1;          // Enable OC1 module


    EnableInterrupts();

    while (1);

    return 0;
}

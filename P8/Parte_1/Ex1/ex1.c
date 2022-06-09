#include <detpic32.h>

int main(void){
    T3CONbits.TCKPS =  7;  // 1:256 -> Fout_prescaler = 778125
    PR3 = 39063;
    TMR3 = 0;   // Reset timer T3 count register

    T3CONbits.TON = 1;

    while(1){
        while(IFS0bits.T3IF != 0);
        IFS0bits.T3IF = 0;
        putChar('.');
    }
}
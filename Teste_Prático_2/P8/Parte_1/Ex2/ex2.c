#include <detpic32.h>

int main(void){
    T3CONbits.TCKPS =  7;  // 1:256 -> Fout_prescaler = 778125
    PR3 = 39063;
    TMR3 = 0;   // Reset timer T3 count register

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
   

    T3CONbits.TON = 1;

    EnableInterrupts();
    
    while(1);
    
    return 0;


}


void _int_(12) isr_T3(void)
{
    putChar('.');
    IFS0bits.T3IF = 0;
}
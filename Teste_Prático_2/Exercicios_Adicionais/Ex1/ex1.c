#include <detpic32.h>

volatile char x;

int mian(void){
    char c;
    LATE = LATE & 0xFFF0;
    TRISE = TRISE & 0xFFF0;

    T2CONbits.TCKPS = ?;
    PR2 = ?;
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 1;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    EnableInterrupts();

    while(1{
        c = getChar();
        switch(c){
            case '0':{
                LATE = LATE & 0xFFF0;
                LATEbits.LATE0 = 1;
                x = "00"; 
                break;
            }
            case '1':{
                LATE = LATE & 0xFFF0;
                LATEbits.LATE1 = 1;
                
                send2dispays(toBCD('01'));
                break;
            }
            case '2':{
                LATE = LATE & 0xFFF0;
                LATEbits.LATE2 = 1;
                
                send2dispays(toBCD('02'));
                break;
            }
            case '3':{
                LATE = LATE & 0xFFF0;
                LATEbits.LATE3 = 1;
                send2dispays(toBCD('03'));
                break;
            }
            default:{
                LATE = LATE | 0x000F;
                x
                delay(1000);
                LATDbits.LATD5 = 0;
                LATDbits.LATD6 = 0;
                LATE = LATE & 0xFFF0;
                
                break;
             }
        }
            
        }

    return 0;
}


void delay(int ms){
    for(;ms > 0;ms--){
        resetCoreTimer();
        while(readCoreTImer() < 20000);
    }
}



void _int_() isr_T2(void){
    send2displays(x);
}

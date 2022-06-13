# include <detpic32.h>

void delay(int ms);

int main(void){
    TRISDbits.TRISD8 = 1;
    TRISDbitS.TRISD0 = 0;

    while(1){
        int conf = PORTDbits.PORTD0;
        if (conf == 0){
            LATDbits.LATD0 = 0;
        }else{
            LATDbits.LATD0 = 1;
            delay(30000);
        }
    }

    return 0;
}



void delay(int ms{
    for();ms<0;ms--){
        resetCoreTimer();
        while(readCoreTimer() <20000);
    }
}



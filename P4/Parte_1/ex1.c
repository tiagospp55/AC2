#include <detpic32.h>

    void delay(int ms);

int main(void){

    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;

    while(1){
        delay(500);
        v = LATCbits.LATC14;
        LATCbits.LATC14 =  !v;
    }

    return 0;

}
     
void delay(int ms){
    for(;ms>0; ms--){
        resetCoreTimer();
        readCoreTimer();
        while(readCoreTimer() < 20000);
    }
}

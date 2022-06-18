#include <detpic32.h>

    void delay(int ms);

int main(void){

    int cnt = 0;

    LATE = LATE & 0xFFF0;
    TRISE = TRISE & 0xFFF0;

    while(1){
        
        LATE = (LATE & 0xFFF0) | cnt;
        cnt++;
        delay(250);
        

        if (cnt > 15){
            cnt = 0;
        }
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

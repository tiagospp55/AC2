#include <detpic32.h>

void delay(unsigned int ms);

int main(void){
    unsigned int cnt1 = 0, cnt5 = 0, cnt10 = 0;

    while(1){
        delay(100);
        if(cnt10 % 2 == 1){cnt5++;}
        if(cnt10%10 == 9){cnt1++;}
        cnt10++;
        printInt(cnt10, 10|5<<16);
        putchar(' ');
        printInt(cnt5, 10|5<<16);
        putchar(' ');
        printInt(cnt1, 10|5<<16);
        putchar('\r');
    }
    return 0;
}


void delay(unsigned int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000u * ms);
}
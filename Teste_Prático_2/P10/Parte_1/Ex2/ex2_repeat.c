#include <detpic32.h>

int main(void){

    // Configure UART2
    U2MODEbits.ON = 0;          // Disable UART2

    U2BRG = 10;                 // U2BRG = (20Mhz / (16*115200))-1 ~ 10          
    U2MODEbits.PDSEL = 0b00;    // 00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;       // only 1 stop bit
    U2MODEbits.BRGH = 0;        // divide by 16
    U2STAbits.URXEN = 1;        // Enable Receiver
    U2STAbits.UTXEN = 1;        // Enable Transmitter
    U2MODEbits.ON = 1;          // Enable UART2


    while(1){
        putChar('+');
        delay(1000);//wait(1);
    }
}


void putChar(char byte){
    while(U2STABITS.UTXBF == 1);//wait while UART2 UTXBF == 1
    U2TXREG = byte;
    //Copy byte to the U2TXREG register
}

void delay(int ms)
{
    for(;ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}
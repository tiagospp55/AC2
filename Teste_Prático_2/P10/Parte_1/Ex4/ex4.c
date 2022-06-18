#include <detpic32.h>

int main(void){
    
    configUart(1200, '0', 2);

    while(1){
        putstr("String de teste");
        delay(1000);
    }

    return 0;
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

void putstr(char *str){
    for(; *str != '\0' ; *str++){
        putc(*str);
    }
    }
}


void configUart(unsigned int baud, char parity, unsigned int stopbits)
{
    // Configure UART2
    if (baud >= 600 && baud <= 115200)
        U2BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1;    // Aproximate to closest baudrate
    else
        U2BRG = 10;                     // DEFAULT 115200 baudrate
    
    if (parity == 'N')
        U2MODEbits.PDSEL = 0b00;        // 00 = 8-bit data, no parity
    else if (parity == 'E')
        U2MODEbits.PDSEL = 0b01;        // 01 = 8-bit data, even parity
    else if (parity == 'O')
        U2MODEbits.PDSEL = 0b10;        // 10 = 8-bit data, odd parity
    else
        U2MODEbits.PDSEL = 0b00;        // DEFAULT NO PARITY 8 BITS

    if (stopbits == 1 || stopbits == 2)  
        U2MODEbits.STSEL = stopbits - 1;// Number of stopbits
    else
        U2MODEbits.STSEL = 0;           // DEFAULT 1 STOPBIT

    U2MODEbits.BRGH = 0;                // Divide by 16
    U2STAbits.URXEN = 1;                // Enable Receiver
    U2STAbits.UTXEN = 1;                // Enable Transmitter
    U2MODEbits.ON = 1;                  // Enable UART2
}
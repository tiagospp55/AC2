#include <detpic32.h>

int main(void){
    
    char c;
    configAll();

    while(1){}
        c = getc();
        putc(c);
    }
}

void configAll(void){
    U2MODEbits.ON = 0;
    U2MODEbits.BRGH = 0;
    U2BRG = 10;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2SRAbits.URXEN = 1;
    U2MODEbits.ON = 1;
}



int getc(void){
    int c;
    while(U2STAbits.URXDA == 0);
    c = U2RXREG;
    return c;
}

void putc(char c){
    while(U2STAbits.URXDA != 0);
    U2RXREG = c;
}

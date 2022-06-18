#include <detpic32.h>

void delay(int ms);
void send2display_high();
void send2display_low();
void send2display_all();

int main(void){

    TRISE = TRISE & 0xFF80;
    TRISB = TRISB | 0x0003;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
while(1){
    
    int op = PORTB & 0x0003;
    int cont = 0;

    LATE = (LATE $ 0xFF00) | cont;

    cont++;
    if (cont == 60) { cont = 0;}
    delay(200);

    switch(op){
        case(0):{
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 0;
        }
        case(1):{
            char c;
            c = inkey();
            if(c > 0x30 && c < 0x39){
                send2display(toBcd(c,0));
            }
        }
        case(2):{
             char c;
            c = inkey();
            if(c > 0x30 && c < 0x39){
                send2display(0,c);
            }
        }
        case(3):{
             char c;
            c = inkey();
            if(c > 0x30 && c < 0x39){
                send2display_all(c,c);
            }
        }
    }
}


}


void delay(int ms){
    for (;ms > 0; i--){
        resetCoreTimer();
        readCoreTimer();
        while(readCoreTimer < 20000);
    }
}


void send2display(unsigned char value1,unsigned char value2){

     static const char codes[] ={0x3F,
                                0x06,
                                0x5B, 
                                0x4F, 
                                0x66, 
                                0x6D, 
                                0x7D,
                                0x07, 
                                0x7F, 
                                0x6F, 
                                0x77, 
                                0x7C, 
                                0x39, 
                                0x5E, 
                                0x79, 
                                0x71};

    static   char flag = 0;
        if(flag == 0){
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
            LATB = (LATB & 0x80FF) | (display7Scodes[(unsigned int)value1]<<8);
            delay(1);
        }
        else {
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
            LATB = (LATB & 0x80FF) | ((display7Scodes[(unsigned int)value2 << 4] <<8);
            delay(1);
        }
        flag = !flag;
}
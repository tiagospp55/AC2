#include <detpic32.h>

int main(void){

static const char display7Scode[] = {
                                        0x3F, //0
                                        0x06, //1
                                        0x5B, //2
                                        0x4F, //3
                                        0x66, //4
                                        0x6D, //5
                                        0x7D, //6
                                        0x07, //7
                                        0x7F, //8
                                        0x6F, //9
                                        0x77, //A
                                        0x7C, //b
                                        0x39, //C
                                        0x5E, //d
                                        0x79, //E
                                        0x71  //F
    };
    TRISDbits.TRISD5 = 0;
    LATDbits.LATD5 = 1;

    TRISB = TRISB | 0x000F;
    TRISB = TRISB & 0x80FF;

    int index;
    int value;

    while(1))
    {
        index = PORTB & 0x000F;
        value = display7code[index];
        LATB = (LATB & 0x80FF)|((unsigned int)value)) << 8;

    }
    
    return 0;

}
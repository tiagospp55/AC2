#include <detpic32.h>

void send2displays(unsigned char value);
void delay(int ms);

int main(void){

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISB = TRISB & 0x80FF;
    LATB = LATB & 0x80FF;
    int i;
    unsigned char var = 0;
    unsigned char cnt = 0;

    while(1){
        
        var = var & 0xFF;
        if (var%2 == 0){
            cnt++;
        }
        send2displays(cont);
        delay(200);
        var++;
    }
    return 0;
}

void delay(int ms)
{
    resetCoreTimer();
    readCoreTimer();
    while(readCoreTimer() < 20000);
}

void send2displays(unsigned char value)
{
    static const char displays7Scodes[] ={
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

    static char displayFlag = 0;

    unsigned char dh = value >> 4;
    unsigned char dl = value & 0x0F;

    dh = display7scodes[dh];
    dl = displays7Scodes[dl];

    if (displayFlag == 0)
    {
        LATD = (LATD | 0x0040) & 0xFFDF;    // Dipslay High active and Display Low OFF
        LATB = (LATB & 0x80FF) | ((unsigned int)(dh)) << 8; // Clean the display and set the right value
    } else {
        LATD = (LATD | 0x0020) & 0xFFBF;    // Display High OFF and Display High active
        LATB = (LATB & 0x80FF) | ((unsigned int)(dl)) << 8; // Clean the display and set the right value
    }
    displayFlag = !displayFlag;
}
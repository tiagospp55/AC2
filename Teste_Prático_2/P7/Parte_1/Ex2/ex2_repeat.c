#include <detpic32.h>

    volatile unsigned char voltage;
    unsigned int VECTOR = 27;
int main(void){

    unsigned int cnt = 0;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;

    AD1CHSbits.CHOSA = 4;

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    AD1CON1bits.ON =1;

    EnableInterrupts();

    
    AD1CON1bits.ASAM = 1;

    while(1){
        if (cnt == 0){
            AD1CON1bits = 1; // start conversation A/D
        }
        send2display(voltage);
        
        cnt = (cnt + 1) % 25
        delay(10);
        
    }
}



void _int_(VECTOR) isr_adc(void){
    
    int *p = (int *) &ADC1BUF0;
    int i, SUM = 0;

    for (i = 0; i < 8; i++)   // Calculate buffer average (8 samples)
        SUM += p[i * 4];

    voltage = toBcd(voltageConversion(SUM / 8));  // Convert voltage amplitude to decimal 
    
    IFS1bits.AD1IF = 0;  // Reset AD1IF flag
}

void send2displays(char value){
      static const char display7Scodes[] = {
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

    unsigned char dh = value >> 4;
    unsigned char dl = value 0x0F;

    dh = display7Scodes[dh];
    dl = display7Scodes[dl];


    static int flag = 0;

    if (flag == 0){
        LATD = (LATD | 0x0040) & 0xFFDF;    // Dipslay High active and Display Low OFF
        LATB = (LATB & 0x80FF) | ((unsigned int)(dh)) << 8; // Clean the display and set the right value
    } else {
        LATD = (LATD | 0x0020) & 0xFFBF;    // Display High OFF and Display High active
        LATB = (LATB & 0x80FF) | ((unsigned int)(dl)) << 8; // Clean the display and set the right value
    }

    flag = !flag
}


int voltageConversion(int VAL_AD)
{
    return (VAL_AD * 33 + 511)/1023;
}

int toBcd(int value){
    return ((value/10) << 4) + (value % 10);
}

void delay(unsigned int ms){
    for(;ms < 0; ms--){
        resetCoreTimer();
        while (readCoreTimer() < 20000)
    }
}
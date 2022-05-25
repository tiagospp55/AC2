#include <detpic32.h>

static volatile int adc_n;
static volatile int adc_val;
void _int(27) isr_adc(void){
    int i;
    int val;

    // toggle RD11
    LATDbits.LATD11 ^= 1;
    // read values and compute their meaning
    val = adc_n / 2;
    for(i = 0; i < adc_n; i++)
        val += (&ADC1BUF0)[4*i];
    adc_val = val/adc_n;
    IFS1bits.AD1IF = 0;
    // start new conversion
    AD1CON1bits.ASAM = 1;
}

static void configure(void){
    TRISDbits.TRISD11 = 0;
    LATDbits.TRISD11 = 1;
    TRISBbits.TRISB4 = 1;
    AD1CON1bits.PCFC4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;

    AD1CON2bits.SIMPI = adc_n - 1
    AD1CON2bits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    IP6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 0;
    enableInterrupts();
}

int main(void){
    adc_n = 4;
    configure();
    // start conversion
    AD1CON1bits = 1;
    while(inkey() != 'q')
    {
        // prime mean
        printInt(adc_val, 0x0004000A);
        putChar('\r');
    }
    return 0;
}
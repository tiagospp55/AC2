#include <detpic32.h>

void delay(unsigned int ms);
//#include "delay.c"

int main(void)
{
  // configure port RC14 as output and set it to 0
  TRISCbits.TRISC14 = 0;
  LATCbits.LATC14 = 0;
  // main loop
  while(inkey() != 'q')
  {
    // wait 0.5s
    delay(500);
    // toggle RC14 port value
    LATCbits.LATC14 ^= 1;
  }
  return 0;
}
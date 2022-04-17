#include <detpic32.h>

void delay(unsigned int ms)
{
  ms *= (unsigned int)(PBCLK / 1000); // convert to timer clock cycles
  resetCoreTimer();
  while(readCoreTimer() < ms)
    ;
}
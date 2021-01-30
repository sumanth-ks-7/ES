#include <lpc214x.h>
#include "timer.h"
#include "pll.h"
#include "interrupt.h"


int main(void)

{
   initClocks();     // Initialize PLL to setup clocks
   initTimer0();     // Initialize Timer0
   IO0DIR = (1<<1);    // Configure pin P0.10 as Output
   IO0PIN = (1<<1);
    
   T0TCR = (1<<0);     // Enable timer
   
   while(1);         // Infinite Idle Loop
}



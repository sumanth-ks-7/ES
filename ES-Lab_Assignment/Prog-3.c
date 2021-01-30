#include <lpc214x.h>

void pll(void);
void delay(unsigned int z);

int main(void)
{
	IO0DIR=0xffffffff;
    pll(); 
	while(1)
	{
	 	    IOSET0 |= (1<<0)  ;
			delay(100);
			IOCLR0 |= (1<<0);
			delay(100);
	}
}

void pll(void)
{
  PLL0CON=0x01;
  PLL0CFG=0x24;
  PLL0FEED=0xaa;
  PLL0FEED=0x55;
  while(!(PLL0STAT&(1<<10)));
  PLL0CON=0x03;
  PLL0FEED=0xaa;
  PLL0FEED=0x55;
  VPBDIV=0x01;
}
void delay(unsigned int z)
{
    T0CTCR=0x0;                                 
    T0TCR=0x00;                 
    T0PR=59;                 
    T0TCR=0x02;                
    T0TCR=0x01;                 
    while(T0TC<z);           
    T0TCR=0x00;                
    T0TC=0;                     
}
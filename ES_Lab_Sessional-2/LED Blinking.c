#include <lpc214x.h>

void pll(void);
void delay(unsigned int j);

int main(void)
{
    unsigned int i;
	IO0DIR=0xffffffff;
    pll(); 
	while(1)
	{
	 	    IOSET0 |= (1<<1)  ;
			delay(500);
			IOCLR0 |= (1<<1);
			delay(500);
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
void delay(unsigned int j)
{
    T0CTCR=0x0;                                 
    T0TCR=0x00;                 
    T0PR=59999;                 
    T0TCR=0x02;                
    T0TCR=0x01;                 
    while(T0TC<j);           
    T0TCR=0x00;                
    T0TC=0;                     
}
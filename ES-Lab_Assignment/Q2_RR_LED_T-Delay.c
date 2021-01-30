#include<lpc214x.h>
#include<stdio.h>



void initPLL(void)
 {
 // To generate 60MHz from 12MHz crystal
 PLL0CFG=0X24; // SET PSEL=2 AND MSEL=5
 PLL0CON=0X01; //PLL IS ACTIVE BUT NOT YET CONNECT
 PLL0FEED=0XAA; //FEED SEQUENCE
 PLL0FEED=0X55;
 while((PLL0STAT & 0X400)==0);
//WAIT FOR FEED SEQUENCE TO BE INSERTED
 PLL0CON=0X03; // PLL HAS BEEN ACTIVE AND BEING CONNECTRD
 VPBDIV=0X01; // SET PCLK SAME AS FCCLK
 PLL0FEED=0XAA; //FEED SEQUENCE
 PLL0FEED=0X55; //FEED SEQUENCE
 }
 
void delayMS(unsigned int microseconds)
//Using Timer0
{
T0CTCR = 0x00 ; // configure T0 as Timer
T0PR = 60-1 ;
T0TCR = 0x02; //Reset Timer
T0TCR = 0x01; //Enable timer
while(T0TC < microseconds);
//wait until timer counter reaches the desired delay
T0TCR = 0x00; //Disable timer
}

int N=16;
int main()
{
	
	PINSEL2=0X00000000;
	IODIR1=0XFFFFFFFF;
	
	while(1)
	{
		
		if(N==24)
		{
			N=16;
		}
		
		IOSET1=(1<<N);
		delayMS(1000);
		IOCLR1=(1<<N);
		delayMS(1000);
		N++;
	}
}

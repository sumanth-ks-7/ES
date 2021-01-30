#include<lpc214x.h>
#define led1 16
#define led2 17
#define led3 18
#define led4 19

void initserial(void)
{
PINSEL0 =0X05;
// P0.0 = TxD , P0.1 = RxD
U0LCR = 0X83;
// DLAB(7) = 1 , 8 Bit UART (1,0) = 1,
U0DLL = 0X87;
// = 60 x 10^6 / (9600 x 16) = 391 = 0x0187
U0DLM = 0X01; // 9600 Baud
U0LCR = 0X03; // DLAB(7) = 0,8 Bit UART (1,0) = 1,
}

unsigned char receiveserial(void)
{
unsigned char mydata ;
while((U0LSR & 0x01)==0);
// wait until RBR Full Flag is set.
mydata = U0RBR ;
// Move data Received to U0THR
return mydata;
}


void initPLL()
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

 /*void sendserial(unsigned char serdata)
{
U0THR = serdata;
// Move data to be transmitted to U0THR
while((U0LSR & 0x20)==0);
// wait until THR Empty Flag is set.
}*/

void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<2000;j++);
	}
}

 unsigned char UARTdata[14];
 int i;


 int main(void)
 {
	 char ch;
	 
	 
 initPLL(); // 60 MHz Pclk
 initserial();
	 PINSEL2=0X00000000;
	 IODIR1 = (1<<led1);
	 IODIR1 = (1<<led2);
	 IODIR1 = (1<<led3);
	 IODIR1 = (1<<led4);
	 
 while(1)
 {
 ch=receiveserial();
	 if(ch==1)
	 {
		IOPIN1=(1<<led1); 
		 
	 }
	 else if(ch==2)
	 {
		 IOPIN1=(1<<led2);
	 }
	 else if(ch==3)
	 {
		 IOPIN1=(1<<led3);
	 }
	 else if(ch==4)
	 {
		 IOPIN1=(1<<led4);
	 }
 
 delay(1000);
}
}

 
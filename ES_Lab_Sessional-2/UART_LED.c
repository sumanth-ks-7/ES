#include <lpc214x.h>

#define RDR (1<<0) 
#define THRE (1<<5) 
#define MULVAL 15
#define DIVADDVAL 1
#define NEW_LINE 0xA 
#define ENTER 0xD 

void pll()                  
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

void InitUART0()
{
  PINSEL0 = 0x500;  
  U0LCR	= 3 | (1<<7) ; 
  U0DLL	= 110;
  U0DLM = 1;	
  U0FDR = (MULVAL<<4) | DIVADDVAL; 
  U0LCR &= 0x0F; 
  
 
}

void delay(unsigned int z)
{
    T0CTCR=0x0;                 
    T0TCR=0x00;                
    T0PR=59999;                 
    T0TCR=0x02;                
    T0TCR=0x01;                 
    while(T0TC<z);           
	    T0TCR=0x00;                 
	    T0TC=0;                     
}

char U0Read()
{
     while( !(U0LSR & RDR ) ); 
     return U0RBR; 
}

void U0Write(char data)
{
     while ( !(U0LSR & THRE ) ); 
     
     U0THR = data;
}

int main(void)
{
	pll(); 
	InitUART0();
	IO1DIR |= 0xFFFFffff;
	
	while(1)		
	{
		char c = U0Read(); 
		switch (c) {
		case 'a':
			U0Write(NEW_LINE);
			IOSET1 |= (1<<16);
			delay(100);
			IOCLR1 |= (1<<16);
	
			break;

		case 'b':
			U0Write(NEW_LINE);
			IOSET1 |= (1<<17);
			delay(100);
			IOCLR1 |= (1<<17);
		
			break;

		case 'c':
			U0Write(NEW_LINE);
			IOSET1 |= (1<<18);
			delay(100);
			IOCLR1 |= (1<<18);
			
			break;

		default:
			 IOCLR1 |= 0xFFFFffff;
		}
	}	
}
#include <lpc214x.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>	

#define STRLEN 5
#define NEW_LINE 0xA // Character for new line .. analogous to '\n'
#define ENTER 0xD
 
void pll()
{
 PLL0CON=0X01;
 PLL0CFG=0X24;
 PLL0FEED=0XAA;
 PLL0FEED=0X55;
 while((PLL0STAT&(1<<10))==0);
 PLL0CON=0X03;
 PLL0FEED=0XAA;
 PLL0FEED=0X55;
 VPBDIV=0x01; //pclk=60mhz
}
void delay(unsigned int z)
{
    T0CTCR=0x0;                 //Select Timer Mode
    T0TCR=0x00;                 //Timer off
    T0PR=59999;                 //Prescaler value for 1ms
    T0TCR=0x02;                 //Timer reset
    T0TCR=0x01;                 //Timer ON
    while(T0TC<z);           
	    T0TCR=0x00;                 //Timer OFF
	    T0TC=0;                     //Clear the TC value. This is Optional.
}

 
void ser_int()
{
 PINSEL0=0X5;
 U0LCR=0X83;
 U0DLL=135;
 U0DLM=1;
 U0LCR=0X03;
}
 
void tx(unsigned char c)
{
 while((U0LSR&(1<<5))==0);
 U0THR=c;
}
 
char rx()
{
 unsigned char a;
 while((U0LSR&(1<<0))==0);
 a=U0RBR;
 return a;
}									   
 
int main(void)
{
	unsigned char a[STRLEN];
	unsigned char b[STRLEN];
	unsigned char v[5] = {'a', 'e', 'i', 'o', 'u'};
	unsigned int i, j, k, l, m, o, p, z, x, y, count, countV;
	
	pll();
	ser_int();
	PINSEL1 |= 0x00;
	IO1DIR |= 0xFFFFffff;
 	while(1) {
	 	for (i = 0; i < STRLEN; i++) {
	 		a[i] = rx();
	 	}
		
		x = STRLEN;
		for (k = 0; k < STRLEN; k++) {
	 		if (x >= 0) {
				b[x-1] = a[k];
				x--;
			}
	 	}

	 	for (j = 0; j < STRLEN; j++) {
	 		tx(a[j]);
	 	}
		tx(NEW_LINE);
		for (l = 0; l < STRLEN; l++) {
	 		tx(b[l]);
	 	}

		for (m = 0; m < STRLEN; m++) {
			if (a[m] == b [m]) {
				count++;
			}
		}
		tx(NEW_LINE);
		if (count == STRLEN) {
			tx('y');
			count = 0;
			tx(NEW_LINE);
			IO1SET |=  (1<<16);
		}
		if (count != STRLEN) {
			IO1CLR |= (1<<16);
			y = 0;
			for (p = 0; p < STRLEN; p++) {
				for(o = 0; o < STRLEN; o++) {
					if (v[y] == a[o]) 	countV++;
					else 				continue;
				}
				y++;
			}
			for(z = 0; z < countV; z++) {
				 IO1SET |=  (1<<16);
				 delay(100);
				 IO1CLR |=  (1<<16);
				 delay(100);
			}
			countV = 0;
			y = 0;	
		}					 
 	}
 }
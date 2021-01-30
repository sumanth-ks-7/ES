#include<lpc214x.h>

int N=16;
void delay(int x)
{
	int i;
	for(i=0;i<x;i++);

}

int main()
{
	PINSEL2=0X00000000;
	IODIR1=0XFFFFFFFF;
	
	while(1)
	{
		
		if(N==21)
		{
			N=16;
		}
		
		IOSET1=(1<<N);
		delay(100000);
		IOCLR1=(1<<N);
		delay(100000);
		N++;
	}
}


#include<lpc214x.h>

#define led 20
#define switch1 31


int main()
{
	 unsigned int  switchStatus;

    PINSEL2 = 0x00000000; //Configure the PORT1 Pins as GPIO;
    
    IODIR1 = ((1<<led) | (0<<switch1)); // LED pin as output and Switch Pin as input 
		
	
	while(1)
	{
		
		switchStatus = (IOPIN1>>switch1) & 0x01 ;  // Read the switch status
       
       if(switchStatus == 1)                 //Turn ON/OFF LEDs depending on switch status
       {  
         IOPIN1 = (1<<led);
       }
       else
       {
         IOPIN1 = (0<<led);
       }      
	}
}

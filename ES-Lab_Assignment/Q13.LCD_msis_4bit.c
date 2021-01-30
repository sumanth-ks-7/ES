#include<lpc214x.h>
 
#define bit(x) (1<<x)
 
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();
 
#define delay for(i=0;i<55000;i++)
 
unsigned int range=0,i;
 
int main()
{
    VPBDIV=0x01;                 // PCLK = 60MHz
    IO0DIR=0x0FC;
    lcd_init();
    cmd(0x89);
    show("MSIS");
 
    while(1) {
        cmd(0x18);
        delay;
    }
}
 
void lcd_init()
{
        cmd(0x02);
    cmd(0x28);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x80);
}
 
void cmd(unsigned char a)
{
    IO0PIN&=0xffffff03;
    IO0PIN|=(a & 0xf0) << 0;
    IO0CLR|=bit(2);                //rs=0
    IO0CLR|=bit(1);                //rw=0
    IO0SET|=bit(3);                 //en=1
    lcd_delay();
    IO0CLR|=bit(3);                 //en=0
    
    IO0PIN&=0xffffff03;
    IO0PIN|=((a << 4)  & 0xf0) << 0;
    IO0CLR|=bit(2);                //rs=0
    IO0CLR|=bit(1);                //rw=0
    IO0SET|=bit(3);                 //en=1
    lcd_delay();
    IO0CLR|=bit(3);                 //en=0
}
 
void dat(unsigned char b)
{
    IO0PIN&=0xffffff03;
    IO0PIN|=(b & 0xf0) << 0;
    IO0SET|=bit(2);                //rs=1
    IO0CLR|=bit(1);                //rw=0
    IO0SET|=bit(3);            //en=1
    lcd_delay();
    IO0CLR|=bit(3);            //en=0
    
    IO0PIN&=0xffffff03;
    IO0PIN|=((b << 4)  & 0xf0) << 0;
    IO0SET|=bit(2);                //rs=1
    IO0CLR|=bit(1);                //rw=0
    IO0SET|=bit(3);            //en=1
    lcd_delay();
    IO0CLR|=bit(3);            //en=0
}
 
void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}
 
void lcd_delay()
    {
    unsigned int i;
    for(i=0;i<=1000;i++);
}
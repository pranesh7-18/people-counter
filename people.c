#include<reg51.h>

#define lcd P2
sbit rs=P0^0;
sbit en=P0^3;

sbit ir1=P1^7;
sbit ir2=P1^0;

void lcd_init(void);
void cmd(unsigned char);
void Data(unsigned char);
void lcd_string(unsigned char *);
void delay(unsigned int);
void IntegerDisplay(unsigned int);

unsigned int count=0;

void main(void)
{
	lcd_init();
	

	while(1)
	{
		cmd(0x80);
		lcd_string("People count:");
		cmd(0xc8);
		if(ir1==1)
		{
			while(ir1==1);
			while(ir2==0);
			while(ir2==1);
			count++;
		}
		else if(ir2==1)
		{
			while(ir2==1);
			while(ir1==0);
			while(ir1==1);
			if(count>0)
			{
				count--;
			}
		}
		IntegerDisplay(count);
	}
}

void lcd_init(void)
{
	cmd(0x38);
	cmd(0x0e);
	cmd(0x06);
	cmd(0x01);
	cmd(0x0c);
}

void cmd(unsigned char ch)
{
	lcd=ch;
	rs=0;
	en=1;
	delay(1000);
	en=0;
}

void Data(unsigned char ch)
{
	lcd=ch;
	rs=1;
	en=1;
	delay(1000);
	en=0;
}

void lcd_string(unsigned char *s)
{
	while(*s)
		Data(*s++);
}

void delay(unsigned int n)
{
	int i;
	for(i=0;i<n;i++);
}

void IntegerDisplay(unsigned int num)
{
	cmd(0x04);
	if(num==0)
	{
		Data('0');
	}
	else
	{
		while(num!=0)
		{
			Data((num%10)+'0');
			num/=10;
		}
	}
	cmd(0x06);
}

	
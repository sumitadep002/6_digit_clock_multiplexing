/*
 * avr_clock.cpp
 *
 * Created: 16-07-2022 16:08:00
 * Author : Sumit
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <GPIO.h>
#define  D1 PB0
#define  D2 PB1
#define  D3 PB2
#define  D4 PB3
#define  D5 PB4
#define  D6 PB5
unsigned char NUM[]={0X02,0X9E,0X24,0X0C,0X98,0X48,0x40,0X1E,0X00,0X08};

void display(uint8_t number)
{
	PORTD=NUM[number];
}

void digit(uint8_t c,bool state)
{
	if (state)
	{
		switch(c)
		{
			case 1:
			PORTB|=1<<D1;
			break;
			case 2:
			PORTB|=1<<D2;
			break;
			case 3:
			PORTB|=1<<D3;
			break;
			case 4:
			PORTB|=1<<D4;
			break;
			case 5:
			PORTB|=1<<D5;
			break;
			case 6:
			PORTB|=1<<D6;
			break;
		}
	}
	else
	{
		switch(c)
		{
			case 1:
			PORTB&=(~(1<<D1));
			break;
			case 2:
			PORTB&=(~(1<<D2));
			break;
			case 3:
			PORTB&=(~(1<<D3));
			break;
			case 4:
			PORTB&=(~(1<<D4));
			break;
			case 5:
			PORTB&=(~(1<<D5));
			break;
			case 6:
			PORTB&=(~(1<<D6));
			break;
		}
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD=0XFF;
	DDRB=0XFF;
	PORTB=0X00;
    while (1) 
    {
		/*display(1);       //digit 1
		digit(1,1);
		digit(2,0);
		digit(3,0);
		digit(4,0);
		digit(5,0);
		digit(6,0);
		_delay_ms(1);
		
		display(0);			//digit 2
		digit(1,0);
		digit(2,1);
		digit(3,0);
		digit(4,0);
		digit(5,0);
		digit(6,0);
		_delay_ms(1);
		
		display(0);			//digit 3
		digit(1,0);
		digit(2,0);
		digit(3,1);
		digit(4,0);
		digit(5,0);
		digit(6,0);
		_delay_ms(1);
		
		display(0);				//digit 4
		digit(1,0);
		digit(2,0);
		digit(3,0);
		digit(4,1);
		digit(5,0);
		digit(6,0);
		_delay_ms(1);
		
		display(0);				//digit 5
		digit(1,0);
		digit(2,0);
		digit(3,0);
		digit(4,0);
		digit(5,1);
		digit(6,0);
		_delay_ms(1);
		
		display(0);				//digit 6
		digit(1,0);
		digit(2,0);
		digit(3,0);
		digit(4,0);
		digit(5,0);
		digit(6,1);
		_delay_ms(1);
		
		display(0);
		digit(1,0);
		digit(2,0);
		digit(3,0);
		digit(4,0);
		digit(5,0);
		digit(6,0);
		_delay_ms(1);*/

		display(5);
		digit(6,1);
		_delay_ms(1000);
		digit(6,0);



    }
}


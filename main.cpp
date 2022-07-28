#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DIGIT1 PB0
#define DIGIT2 PB1
#define DIGIT3 PB2
#define DIGIT4 PB3
#define DIGIT5 PB4
#define DIGIT6 PB5
#define hour_switch PC0
#define minute_switch PC1

uint16_t time=0;
uint8_t hour=0;
uint8_t minute =0;
uint8_t second =0;





#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
	// the fractional number of milliseconds per timer0 overflow. we shift right
	// by three to fit these numbers into a byte. (for the clock speeds we care
	// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)


volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

volatile uint8_t count;

ISR (TIMER0_OVF_vect)

{


	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;





}

unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	cli();
	m = timer0_millis;
	SREG = oldSREG;

	return m;
}


uint8_t NUM[10]={0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,0X00,0X10};

void display_number(uint8_t num)
{
	switch(num)
	{
		case 0:
		PORTD=NUM[0];
		break;
		case 1:
		PORTD=NUM[1];
		break;
		case 2:
		PORTD=NUM[2];
		break;
		case 3:
		PORTD=NUM[3];
		break;
		case 4:
		PORTD=NUM[4];
		break;
		case 5:
		PORTD=NUM[5];
		break;
		case 6:
		PORTD=NUM[6];
		break;
		case 7:
		PORTD=NUM[7];
		break;
		case 8:
		PORTD=NUM[8];
		break;
		case 9:
		PORTD=NUM[9];
		break;
		case 10:
		PORTD=0XFF;
		break;
	}
	
}

void display_unit(uint8_t n,bool action)
{
	switch(n)
	{
		case 1:
		if(action)	PORTB|=(1<<DIGIT1);
		else	PORTB&=(~(1<<DIGIT1));
		break;
		
		case 2:
		if(action)
		PORTB|=(1<<DIGIT2);
		else PORTB&=(~(1<<DIGIT2));
		break;
		
		case 3:
		if(action)
		PORTB|=(1<<DIGIT3);
		else
		PORTB&=(~(1<<DIGIT3));
		break;
		
		case 4:
		if(action)
		PORTB|=(1<<DIGIT4);
		else
		PORTB&=(~(1<<DIGIT4));
		break;
		
		case 5:
		if(action)
		PORTB|=(1<<DIGIT5);
		else
		PORTB&=(~(1<<DIGIT5));
		break;
		
		case 6:
		if(action)
		PORTB|=(1<<DIGIT6);
		else
		PORTB&=(~(1<<DIGIT6));
		break;
		
	}
}
void all_display_off()
{
	PORTB=0X00;
}

void display(uint16_t t)
{
	display_unit(DIGIT6,1);
	display_number(t%10);
	_delay_us(500);
	display_unit(DIGIT6,0);
	t=t/10;
	display_unit(DIGIT5,1);
	display_number(t%10);
	_delay_us(500);
	display_unit(DIGIT5,0);
	t=t/10;
	display_unit(DIGIT4,1);
	display_number(t%10);
	_delay_us(500);
	display_unit(DIGIT4,0);
	t=t/10;
	display_unit(DIGIT3,1);
	display_number(t%10);
	_delay_us(500);
	display_unit(DIGIT3,0);
	t=t/10;
	display_unit(DIGIT2,1);
	display_number(t%10);
	_delay_us(500);
	display_unit(DIGIT2,0);
	t=t/10;
	display_unit(DIGIT1,1);
	display_number(t%10);
	_delay_us(500);
	display_unit(DIGIT1,0);
	t=t/10;
}

int main(void)
{
	TCNT0 = 0;
	count = 0;
	TCCR0B |= (0<<CS02) | (1<<CS01) | (1<<CS00); // PRESCALER 64
	TIMSK0 = (1<<TOIE0);
	sei();

	DDRD=0XFF;
	DDRB=0XFF;
	DDRC=0X00;
	PORTC=0XFF;
	unsigned long current_time = millis();
	unsigned long start_time = 0;
	unsigned long start_time_switch = 0;

	while(1)
	{
		if(current_time - start_time > 1000)
		{
			second++;
			start_time=current_time;
		}
		if(!(PINC&(1<<hour_switch)))
		{
			if(current_time-start_time_switch > 200)
			hour++;
			start_time_switch=current_time;
		}
		if (!(PINC&(1<<PC0)))
		{
			if(current_time-start_time_switch > 200)
			minute++;
			second=0;
			start_time=current_time;
		}
		
		if (second >59)
		{
			second=0;
			minute++;
		}
		if (minute>59)
		{
			minute=0;
			hour++;
		}
		if (hour>12)
		{
			hour=1;
		}
		time=hour*10000+minute*100+second;
		display(time);
		
	}
	
	
}

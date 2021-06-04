#include "stdint.h"
#include "tm4c123gh6pm.h"


void ports_led_init(){
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0x20;     //PORTF_CLK_LED
	while((SYSCTL_RCGCGPIO_R & 0x20) == 0);   //WAIT FOR CLOCK                  
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock PORTF
	GPIO_PORTF_CR_R |= 0x04;
  GPIO_PORTF_DIR_R |= 0x04;      //LED_OUTPUT
	GPIO_PORTF_AFSEL_R = 0;        //OFF ALTERNATE FOR LED
	GPIO_PORTF_PCTL_R = 0;     
	GPIO_PORTF_AMSEL_R = 0;        //NOT_ANALOG
	GPIO_PORTF_DEN_R |= 0x04;      //enable-digital
}

void led(int x)
{
	if(x >= 100)
	{
		GPIO_PORTF_DATA_R |= 0x04;
	}
}
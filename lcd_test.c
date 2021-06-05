#include "stdint.h"
#include "tm4c123gh6pm.h"

// delay function
void Delay() {
    unsigned long  time;
    time = 500;
    while(time){
        time--;
    }
}

//intiliaztion of port B as data pins
void lcd_data_ports_init(){
    SYSCTL_RCGCGPIO_R |= 0x02;   //clock B
    while((SYSCTL_RCGCGPIO_R & 0x02) == 0);
    GPIO_PORTB_LOCK_R = 0x4C4F434B;   //unlock port B
    GPIO_PORTB_CR_R |= 0xFF;
    GPIO_PORTB_DIR_R |= 0xFF;     //set as ouput
    GPIO_PORTB_DEN_R |= 0xFF;     // set as digital
    GPIO_PORTB_AFSEL_R = 0;       // lock alternationg
    GPIO_PORTB_PCTL_R = 0;
    GPIO_PORTB_AMSEL_R = 0;       //lock analog
}

//intailize pin 5,6,7 of port A as control pins to lcd
void lcd_control_ports_init(){
    SYSCTL_RCGCGPIO_R |= 0x01;   //clock B
    while((SYSCTL_RCGCGPIO_R & 0x01) == 0);
    GPIO_PORTA_LOCK_R = 0x4C4F434B;   //unlock pins in port A
    GPIO_PORTA_CR_R |= 0xE0;
    GPIO_PORTA_DIR_R |= 0xE0;     // set as ouput
    GPIO_PORTA_DEN_R |= 0xE0;     // set as digital
    GPIO_PORTA_AFSEL_R = 0;       //lock alternating
    GPIO_PORTA_PCTL_R = 0;     
    GPIO_PORTA_AMSEL_R = 0;       //lock analog
}


//send command to lcd
void lcd_command(char command)
{
     GPIO_PORTA_DATA_R = 0;        //RS=0, RW=0
     Delay();
     GPIO_PORTA_DATA_R |= 0x80;   // EN = 1
     Delay();
     GPIO_PORTB_DATA_R = command; //put command on data pins
     Delay();
     GPIO_PORTA_DATA_R = 0;       // EN =0
     Delay();

}

//send data to lcd
void lcd_data(char data)
{
  
    GPIO_PORTA_DATA_R = 0x20;     //RS=1, RW=0 
    Delay();
    GPIO_PORTA_DATA_R |= 0x80;    // EN = 1
    Delay();
    GPIO_PORTB_DATA_R = data;     //put data on data's pins to display on screen
    Delay();
    GPIO_PORTA_DATA_R = 0;       // EN =0
    Delay();
}

//intialize to screen of lcd
void lcd_init(){
	  lcd_data_ports_init();
    lcd_control_ports_init();
	  lcd_command(0x30);   //wakeup 
    Delay();
    lcd_command(0x38);   //8- bits data
    Delay();
    lcd_command(0x01);    //clear
    Delay();
    lcd_command(0x80);   //force cursor to beginging of first line
    Delay();
    lcd_command(0x0F);    //display on
    Delay();
}

void display_distance(int x)
{
	 char h,t,u;
   char d[] = {"Distance: "};
   int i;
   for(i = 0; i < 10; i++){
	lcd_data(d[i]);
	Delay();
   } 
   h = (x / 100) + '0';
   lcd_data(h);
   Delay();
   t = ((x / 10)% 10)+ '0';
   lcd_data(t);
   Delay();
   u = (x % 10) + '0';
   lcd_data(u);
   Delay();
}

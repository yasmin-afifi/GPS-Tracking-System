#define SYSCTL_RCGCGPIO_R (*(( volatile unsigned long *)0x400FE608 ) )
#define GPIO_PORTF_DATA_R (*(( volatile unsigned long *)0x40025038 ) )
#define GPIO_PORTF_DIR_R  (*(( volatile unsigned long *)0x40025400 ) )
#define GPIO_PORTF_DEN_R  (*(( volatile unsigned long *)0x4002551C ) )
#define GPIO_PE54_M 0x30
#define GPIO_PA10_M 0x03
#define Green_LED 0x08
#define pi 3.14159265358979323846

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "lcd.h"
#include "led.h"

float min2degree(float x){
    float y;
    x = x /100.0;
    y = x - (int) x;
    y = y * 100;
    x = (int) x + (y / 60.0);
    return x;
}

float degreestoradians(float x){
    float y;
    y = x * pi / 180.0;
    return y;
}
float rad2degree (float x){
    float y;
    y = x * 180.0 / pi;
    return y;
}

int distance_calculate(float lat_previous,float lat_current,float long_previous,float long_current)
{
    float a;
    float c;
    float dlat=degreestoradians(lat_current-lat_previous);
    float dlong=degreestoradians(long_current-long_previous);
    lat_previous=degreestoradians(lat_previous);
    lat_current=degreestoradians(lat_current);
    a=sin(dlat/2)*sin(dlat/2)+sin(dlong/2)*sin(dlong/2)*cos(lat_previous)*cos(lat_current);
    c=2*atan2(sqrt(a),sqrt(1-a));
    return 6371*c *1000;
}

void UART5_Init(void){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;

    UART5_CTL_R &= ~UART_CTL_UARTEN;
    UART5_IBRD_R = 104;
    UART5_FBRD_R = 11;
    UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART5_CTL_R |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);

    GPIO_PORTE_AFSEL_R |= GPIO_PE54_M;
    GPIO_PORTE_PCTL_R |= (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | (GPIO_PCTL_PE4_U5RX | GPIO_PCTL_PE5_U5TX);
    GPIO_PORTE_DEN_R |= GPIO_PE54_M;
}

void printstring(char *data){
    while(*data){
        UART0_WRITE(*(data++));
    }
}

unsigned int UART0_Available(void){
    return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

unsigned int UART0_READ(void){
    while(UART0_Available() != 1 )  ;
    return (unsigned int) UART0_DR_R&0xFF;
}

void UART0_WRITE(unsigned char data){
    while((UART0_FR_R&UART_FR_TXFF) != 0);
    UART0_DR_R = data;
}


unsigned int UART5_Available(void){
    return ((UART5_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

void UART5_WRITE(unsigned int data){
    while((UART5_FR_R&UART_FR_TXFF) != 0);
    UART5_DR_R = data;
}

unsigned int UART5_READ(void){
    while(UART5_Available() != 1 )  ;
    return (unsigned int) UART5_DR_R&0xFF;
}


void UART0_Init(void){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

    UART0_CTL_R &= ~UART_CTL_UARTEN;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);

        GPIO_PORTA_AFSEL_R |= GPIO_PA10_M;
    GPIO_PORTA_PCTL_R |= (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
    GPIO_PORTA_DEN_R |= GPIO_PA10_M;
}
void PortF_LEDs_Init(void){
    uint32_t delay;
    SYSCTL_RCGCGPIO_R  |= 0x20;
    delay = 1;
    GPIO_PORTF_CR_R = 0x0E;
    GPIO_PORTF_AFSEL_R = 0;
    GPIO_PORTF_PCTL_R = 0;
    GPIO_PORTF_AMSEL_R = 0;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x0E;
}

void SystemInit(){
    UART0_Init();
    UART5_Init();
    PortF_LEDs_Init();
}
int dis = 0;
int count = 0;

int main(void){
       lcd_init();
       ports_led_init();
       SystemInit();
       GPIO_PORTF_DATA_R |= Green_LED;//"$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C"
           unsigned char LED;
           char c0;
           char s1[10];
           char s2[11];
           float temp_lat, temp_lon, lat = 0, lon = 0;
           int i;
           int j;
           int k;
           int flag;
           int x;
           int y;
           char gpsvalue[70];
           int index;



    while(1){
           led(dis);
           display_distance(dis);
           c0 = UART5_READ();
           UART0_WRITE(c0);
           if(c0 == '$'){
               c0 = UART5_READ();
               UART0_WRITE(c0);
               if (c0 == 'G'){
                   c0 = UART5_READ();
                   UART0_WRITE(c0);
                   if(c0 == 'P'){
                       c0 = UART5_READ();
                       UART0_WRITE(c0);
                       if(c0 == 'R') {
                           c0 = UART5_READ();
                           UART0_WRITE(c0);
                           if(c0 == 'M'){
                               c0 = UART5_READ();
                               UART0_WRITE(c0);
                               if(c0 == 'C'){
                                   c0 = UART5_READ();
                                   UART0_WRITE(c0);
                                   index = 0;
                                   while(c0 != '\n'){
                                       gpsvalue[index] = c0;
                                       c0 = UART5_READ();
                                       UART0_WRITE(c0);
                                       index ++;
                                    }
                                    count = 0;
                                    flag = 0;
                                   for(i = 0; i < 70; i++){
                                       if(gpsvalue[i] == ','){
                                           count ++;
                                       }
                                       if (count == 3 && flag == 0){
                                           x =  i+1;
                                           flag = 1;
                                       }
                                       if(count == 4 && flag == 1){
                                           y = i - 1;
                                       }
                                 }

                                 count = 0;
                                 flag = 0;
                                 for (j = x, k = 0; j < y; j++,k++){
                                     s1[k] = gpsvalue[j];
                                 }
                                 temp_lat = lat;
                                 lat = atof(s1);

                                 lat = min2degree(lat);

                                 for(i = 0; i < 70; i++){
                                       if(gpsvalue[i] == ','){
                                           count ++;
                                       }
                                       if (count == 5 && flag == 0){
                                           x = i+1;
                                           flag = 1;
                                       }
                                       if(count == 6 && flag == 1){
                                           y = i - 1;
                                       }
                                 }
                                 for (j = x, k = 0; j < y; j++,k++){

                                     s2[k] = gpsvalue[j];
                                 }
                                 temp_lon = lon;
                                 lon = atof(s2);
                                 lon = min2degree(lon);

                                 if(temp_lon != 0 && temp_lat != 0){
                                     dis += distance_calculate(temp_lat,lat,temp_lon,lon);

                                 }
                              }
                          }
                       }
                     }
                  }
               }
   }
}

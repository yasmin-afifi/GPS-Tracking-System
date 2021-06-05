#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "math.h"
#include "stdbool.h"
#include "LCD.h"


//Distance between two coordinates
double calcDistance(double dLat1,double dLon1 ,double dLat2, double dLon2)
{
 double r = 6371;                            //Earth's radius in kilometers
 double dLat;
 double dLon;
 double a;
 double distance;
 double c = 0;
	
 dLat = dLat2- dLat1;
 dLat /= 57.29577951;
	
 dLon= dLon2-dLon1;
 dLon/= 57.29577951;
 
 dLat1 /= 57.29577951;
 dLat2 /= 57.29577951;
	
 a = (sin(dLat/2)*sin(dLat/2)) +( cos(dLat1)*cos(dLat2)*sin(dLon/2)*sin(dLon/2));
	
 c = 2* atan2(sqrt(a),sqrt(1-a));
	
 distance = r*c;       
 return distance;
}


//intiliaztion of port F pin 4 as switch
void switch_init(){
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0x20;     //PORTF_CLK_LED
	while((SYSCTL_RCGCGPIO_R & 0x20) == 0);   //WAIT FOR CLOCK                  
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock PORTF
	GPIO_PORTF_CR_R |= 0x10;
	
  GPIO_PORTF_DIR_R &= ~0x10;      //switch F4
	GPIO_PORTF_AFSEL_R &= ~0x10;        //OFF ALTERNATE FOR switch
	GPIO_PORTF_PCTL_R &= ~0x10;     
	GPIO_PORTF_AMSEL_R &= ~0x10;        //NOT_ANALOG
	GPIO_PORTF_DEN_R |= 0x10;      //enable-digital
	GPIO_PORTF_PUR_R |= 0x01;
}

//return true if switch is pushed
bool Pushed_Switch()
{
	return ((GPIO_PORTF_DATA_R & 0x10) == 0x00);
	
}

//get Total distance by summing every distance between two coordinates
//stop summing when swich is pushed
double TotDist(){
	double totalDistance = 0;
	double dLat1;
	double dLon1;
	double distance;
	
	while (!Pushed_Switch()){
		
		double dLat2;
		double dLon2;
		Delay();
 		distance = calcDistance( dLat1,dLon1,dLat2,dLon2);
		if (distance>1)
		{
			dLat1 = dLat2;
			dLon1 = dLon2;
			
		  totalDistance += distance;
		}
		
	}
	
return totalDistance;
}





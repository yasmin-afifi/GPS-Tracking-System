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







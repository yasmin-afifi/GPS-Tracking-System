double dis = 0;
double x = 0;
double y = 0;

int main ( void ){

    lcd_init();
    ports_led_init();
    SystemInit(); //"$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C"
        unsigned char LED;
        char c0;
        char *s;
        char s1[10];
        char s2[9];
        double temp_lat, temp_lon, lat = 0, lon = 0;


        for(LED=0x02;LED<=0x08;LED=LED<<1){
                GPIO_PORTF_DATA_R &= ~0x0E;
                GPIO_PORTF_DATA_R=LED;
                One_Second_Delay();
        }


while(1){

       led(dis);
       display_distance((int) dis + 0.5);
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
                                s =  "";
                                while(c0 != '\n'){
                                    c0 = UART5_READ();
                                    UART0_WRITE(c0);
                                    s = strncat(s,&c0,1);
                                 }
                                int i;
                                for(i = 0; i < strlen(s); i++){
                                    if(strcmp(s[i] ,"A")){
                                         strncpy(s1,&s[i+2],10);
                                         temp_lat = lat;
                                         lat =  atof(s1);
                                         break;
                                    }
                                }
                                int j;
                                for(j = 0; j < strlen(s); j++){
                                    if(s[i] == 'N'){
                                        strncpy(s2,&s[i+2],11);;
                                        temp_lon = lon;
                                        lon = atof(s2);
                                    }
                                 }

                                  if(temp_lat != 0 && temp_lon != 0){
                                      dis = calcDistance(temp_lat, temp_lon, lat,lon);

                                  }
                              }
                           }
                       }
                    }
                  }
               }
            }
}
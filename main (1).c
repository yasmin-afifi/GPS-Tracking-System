int dis = 0;
int count = 0;

int main ( void ){

    lcd_init();
    ports_led_init();
    SystemInit(); //"$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C"
        unsigned char LED;
        char c0;
        char *s;
        char s1[10];
        char s2[9];
        float temp_lat, temp_lon, lat = 0, lon = 0;
        int i;
        int j;
        int k;
        int flag;
        int x;
        int y;


        for(LED=0x02;LED<=0x08;LED=LED<<1){
                GPIO_PORTF_DATA_R &= ~0x0E;
                GPIO_PORTF_DATA_R=LED;
        }


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
                                s =  "";
                                while(c0 != '\n'){
                                    c0 = UART5_READ();
                                    UART0_WRITE(c0);
                                    s = strncat(s,&c0,1);
                                 }
                                 count = 0;
                                 flag = 0;
                                for(i = 0; i < strlen(s); i++){
                                    if(s[i] == ','){
                                        count ++;
                                    }
                                    if (count == 3 && flag == 0){
                                        x = i+1;
                                        flag = 1;
                                    }
                                    if(count == 4 && flag == 1){
                                        y = i - 1;
                                    }
                              }
                              count = 0;
                              flag = 0;
                              for (j = x, k = 0; j <= y; j++,k++){
                                  s1[k] = s[j];
                              }
                              temp_lat = lat;
                              lat = atof(s1);
                              for(i = 0; i < strlen(s); i++){
                                    if(s[i] == ','){
                                        count ++;
                                    }
                                    if (count == 5&& flag == 0){
                                        x = i+1;
                                        flag = 1;
                                    }
                                    if(count == 6 && flag == 1){
                                        y = i - 1;
                                    }
                              }
                              for (j = x, k = 0; j <= y; j++,k++){
                                  s2[k] = s[j];
                              }
                              temp_lon = lon;
                              lon = atof(s2);

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
double calcDistance(double dLat1,double dLon1 ,double dLat2, double dLon2)
{
   double distance;
    dLat1 = dLat1 * (pi / 180.0);
    dLat2 = dLat2 * (pi / 180.0);
    dLon1 = dLon1 * (pi / 180.0);
    dLon2 = dLon2 * (pi / 180.0);

    distance = 3963 * acos( sin(dLat1) * sin(dLat2) + cos(dLat1) * cos(dLat2) * cos(dLon2 - dLon1) )*1609.34;
    return distance;

}

void One_Second_Delay(void)
{
    NVIC_ST_CTRL_R = 0;            /* disable SysTick during setup */
    NVIC_ST_RELOAD_R = 15999999;    /* Reload Value goes here */
    NVIC_ST_CTRL_R |= 0x5;          /* enable SysTick with core clock */
    while( (NVIC_ST_CTRL_R & (1<<16) ) == 0);
                                              /* Monitoring bit 16 to be set */
    NVIC_ST_CTRL_R = 0;             /* Disabling SysTick Timer */
}

void delayy(){
    int i;
    int j;
    for(i = 0; i < 2500; i++){
        for(j = 0; j < 2500; j++){

        }
    }
}

void PortF_LEDs_Init(void){
    int delay;
    SYSCTL_RCGCGPIO_R  |= 0x20;
    delay = 1;
    GPIO_PORTF_CR_R = 0x0E;
    GPIO_PORTF_AFSEL_R = 0;
    GPIO_PORTF_PCTL_R = 0;
    GPIO_PORTF_AMSEL_R = 0;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x0E;
}

void Red_ON(void) { GPIO_PORTF_DATA_R |= RED_LED; }
void Red_OFF(void) { GPIO_PORTF_DATA_R &= ~RED_LED; }

void Blue_ON(void) { GPIO_PORTF_DATA_R |= Blue_LED; }
void Blue_OFF(void) { GPIO_PORTF_DATA_R &= ~Blue_LED; }

void Green_ON(void) { GPIO_PORTF_DATA_R |= Green_LED; }
void Green_OFF(void) { GPIO_PORTF_DATA_R &= ~Green_LED; }
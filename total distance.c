float degreestoradians(float x){
    x = x / (pi * 180);
    return x;
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
void Red_ON(void) { GPIO_PORTF_DATA_R |= RED_LED; }
void Red_OFF(void) { GPIO_PORTF_DATA_R &= ~RED_LED; }

void Blue_ON(void) { GPIO_PORTF_DATA_R |= Blue_LED; }
void Blue_OFF(void) { GPIO_PORTF_DATA_R &= ~Blue_LED; }

void Green_ON(void) { GPIO_PORTF_DATA_R |= Green_LED; }
void Green_OFF(void) { GPIO_PORTF_DATA_R &= ~Green_LED; }

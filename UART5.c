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

unsigned int UART5_Available(void){
    return ((UART5_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}



unsigned int UART5_READ(void){
    while(UART5_Available() != 1 )  ;
    return (unsigned int) UART5_DR_R&0xFF;
}


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
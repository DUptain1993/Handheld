
// This is the command sequence that initialises the ST7796 driver
//
// This setup information uses simple 8 bit SPI writecommand() and writedata() functions
//
// See ST7735_Setup.h file for an alternative format

#define TFT_INIT_DELAY 0
{
	writecommand(0x11);     

	delay(120);                //Delay 120ms

	writecommand(0x36);     // Memory Data Access Control MY,MX~~
	writedata(0x48);   

	writecommand(0x3A);     
	writedata(0x55);   //LCD_WR_DATA(0x66);

	writecommand(0xF0);     // Command Set Control
	writedata(0xC3);   

	writecommand(0xF0);     
	writedata(0x96);   

	writecommand(0xB4);     
	writedata(0x01);   

	writecommand(0xB7);     
	writedata(0xC6);   

	//writecommand(0xB9);     
	//writedata(0x02);
	//writedata(0xE0);

	writecommand(0xC0);     
	writedata(0x80);   
	writedata(0x45);   

	writecommand(0xC1);     
	writedata(0x13);   //18  //00

	writecommand(0xC2);     
	writedata(0xA7);   

	writecommand(0xC5);     
	writedata(0x20);   

	writecommand(0xE8);     
	writedata(0x40);
	writedata(0x8A);
	writedata(0x00);
	writedata(0x00);
	writedata(0x29);
	writedata(0x19);
	writedata(0xA5);
	writedata(0x33);

	writecommand(0xE0);
	writedata(0xD0);
	writedata(0x08);
	writedata(0x0F);
	writedata(0x06);
	writedata(0x06);
	writedata(0x33);
	writedata(0x30);
	writedata(0x33);
	writedata(0x47);
	writedata(0x17);
	writedata(0x13);
	writedata(0x13);
	writedata(0x2B);
	writedata(0x31);

	writecommand(0xE1);
	writedata(0xD0);
	writedata(0x0A);
	writedata(0x11);
	writedata(0x0B);
	writedata(0x09);
	writedata(0x07);
	writedata(0x2F);
	writedata(0x33);
	writedata(0x47);
	writedata(0x38);
	writedata(0x15);
	writedata(0x16);
	writedata(0x2C);
	writedata(0x32);
	

	writecommand(0xF0);     
	writedata(0x3C);   

	writecommand(0xF0);     
	writedata(0x69);   

	end_tft_write();
  	delay(120);
  	begin_tft_write();                

	writecommand(0x29);                                       	
}
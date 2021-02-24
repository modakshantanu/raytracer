#include "display.h"
#include "hardware/spi.h"

#include "pico/stdlib.h"


void rst() {
  gpio_put(TFT_RST, 1);
  sleep_ms(500);
  gpio_put(TFT_RST, 0);
  sleep_ms(500);
  gpio_put(TFT_RST, 1);
  sleep_ms(500);
}


void SPIsend(uint8_t byte) {
  spi_write_blocking(spi0, &byte, 1);
  return;
	for (int i = 0x80; i; i >>= 1) {

		byte & i ? gpio_put(MOSI , 1) : gpio_put(MOSI , 0);
		gpio_put(SCL , 1);
		gpio_put(SCL , 0);

		// digitalWrite(MOSI, byte & i);
		// digitalWrite(CLK, HIGH);
		// digitalWrite(CLK, LOW);
	}
}

void command(uint8_t byte) {


	
	// i2c_write(0b10000000);
	// i2c_write(byte);


	gpio_put(DC, 0);
	SPIsend(byte);
}

void data(uint8_t byte) {

	// // i2c_write(0b01000000);
	// i2c_write(byte);
	gpio_put(DC, 1);
	SPIsend(byte);
}



int SWRESET = 0x01;
int SLPOUT = 0x11;
int FRMCTR1 = 0xb1;
int FRMCTR2 = 0xb2;
int FRMCTR3 = 0xb3;

int INVCTR = 0xb4;
int PWCTR1 = 0xc0;
int PWCTR2 = 0xc1;
int PWCTR3 = 0xc2;
int PWCTR4 = 0xc3;
int PWCTR5 = 0xc4;
int VMCTR1 = 0xc5;
int INVOFF = 0x20;
int INVON = 0x21;

int MADCTL = 0x36;
int COLMOD = 0x3a;

int CASET = 0x2a;
int RASET = 0x2b;
int GMCTRP1 = 0xe0;
int GMCTRN1 = 0xe1;

int NORON = 0x13;
int DISPON = 0x29;
int RAMWR = 0x2c;

void window() {
    command(CASET);
  data(0x00);
  data(0x02);
  data(0x00);
  data(128 + 2 - 1);

  command(RASET);
  data(0x00);
  data(0x01);
  data(0x00);
  data(160 + 2 - 1);
  command(RAMWR);
}

void initi() {
  rst();
  command(SWRESET);
  sleep_ms(150);

  command(SLPOUT);
  sleep_ms(500);

  command(FRMCTR1);
  data(0x01);
  data(0x2c);
  data(0x2d);

  command(FRMCTR2);
  data(0x01);
  data(0x2c);
  data(0x2d);

  command(FRMCTR3);
  data(0x01);
  data(0x2c);
  data(0x2d);
  data(0x01);
  data(0x2c);
  data(0x2d);

  command(INVCTR);
  data(0x07);

  command(PWCTR1);
  data(0xa2);
  data(0x02);
  data(0x84);

  command(PWCTR2);
  data(0x0a);
  data(0x00);

  command(PWCTR4);
  data(0x8a);
  data(0xee);

  command(VMCTR1);
  data(0x0e);

  command(INVOFF);

  command(MADCTL);
  data(0xc8);

  command(COLMOD);
  data(0x05);

  command(CASET);
  data(0x00);
  data(0x02);
  data(0x00);
  data(128 + 2 - 1);

  command(RASET);
  data(0x00);
  data(0x01);
  data(0x00);
  data(160 + 2 - 1);

  command(GMCTRP1);
  data(0x02);
  data(0x1c);
  data(0x07);
  data(0x12);
  data(0x37);
  data(0x32);
  data(0x29);
  data(0x2d);
  data(0x29);
  data(0x25);
  data(0x2B); 
  data(0x39);
  data(0x00);
  data(0x01);
  data(0x03);
  data(0x10);

  command(GMCTRN1);
  data(0x03);
  data(0x1d);
  data(0x07);
  data(0x06);
  data(0x2E);
  data(0x2C);
  data(0x29);
  data(0x2D);
  data(0x2E);
  data(0x2E);
  data(0x37);
  data(0x3F);
  data(0x00);
  data(0x00);
  data(0x02);
  data(0x10);


  command(NORON);
  sleep_ms(100);

  command(DISPON);
  sleep_ms(100);


}
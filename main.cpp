/******************************
 * main.c
 * rev 1.0 Jan 2021 shabaz
 * ****************************/

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "display.h"

#include <cstdlib>
#include <math.h>
#include <time.h>

#define setPixel(r,c,cc) (frame[r][2*c] = (cc >> 8), frame[r][2*c+1] = (cc & 0xff))
#define rgb565(r,g,b) (((r) >> 3) | ((g&0b11111100) << 3) | ((b&0b11111000) << 8))

uint8_t frame[160][256];
int height = 160, width = 128;



void render() {

  float aspect_ratio = 128.0/160.0;
  




  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      int r = 0 + (i*240)/height;
      int g = 0 + (i*240)/height;
      int b = 240;

      

      

      setPixel(i,j,rgb565(r,g,b));
    }
  }
}


int main(void) {
    gpio_init(RES);
    gpio_set_dir(RES, GPIO_OUT);

    stdio_init_all();

    spi_init(spi0, 1e9);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 0);

    gpio_init(DC);
    gpio_set_dir(DC, GPIO_OUT);
    gpio_put(DC, 1);


    initi();
    window();

 

    int x = 0;
    int y = 0;
    int dx = 5;
    int dy = 5;
  int i = 0;
    while(1) {
      
    render();
      window();

      i++;
      if (i >=21) i = 0;
      render();
  //     color <<= 1;
  // if (color == 0) color = 1;
      gpio_put(DC, 1);
	    spi_write_blocking(spi0, &frame[0][0], 128*160*2);
      
      


      


      // for (int i = 0; i < 160; i++) {
      //   for (int j = 0; j < 128; j++) {
          

      //     if (sqrt((i-x)*(i-x) + (j - y)*(j-y)) < 10) {
      //       setPixel(i,j,color);
      //       // frame[i][2*j+1] = color;
      //       // frame[i][2*j] = 0;
      //     }
      //     else {
      //       frame[i][2*j+1] = 0;
      //       frame[i][2*j] = 0;
      //     }



      //   }
      // }

      // x += dx;
      // y += dy;
      // if (x < 0 || x > 160) dx = -dx;
      // if (y < 0 || y > 128) dy = -dy;


      sleep_ms(200);
      
    }



    return 0;
}

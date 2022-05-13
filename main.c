#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main() {
  stdio_init_all();
  printf("ADC Example, measuring temperature GPIO26\n");

  adc_init();

  adc_gpio_init(26);
  adc_select_input(0);

  float R1 = 10000.0;
  float Vcc = 3.3;
  float beta = 3950.0;
  float R2 = 0;
  float tension = 0;
  float R2t0 = 10000.0;
  float T = 0;
  const float conversion_factor = 3.3f / (1 << 12);

  while (1) {

    uint16_t result = adc_read();
    tension = result * conversion_factor;
    R2 = R1 / ( Vcc / tension - 1);
    T = beta / ( log( R2 / R2t0 ) + ( beta / 298.f ) );
    
    
    
    printf("Temperature %.2f C, resistance: %.2f \n", T - 273, R2);
    sleep_ms(500);
  }
}
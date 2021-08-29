#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "linear-encoder.c"

void onchange(linear_encoder_t *encoder) {
  printf("onchange: %d\n", encoder->value);
}

int main() {
  stdio_init_all();
  linear_encoder_t *encoder = create_encoder(26, onchange);
  while (true) tight_loop_contents(); // everything is interrupt driven
  return 0;
}

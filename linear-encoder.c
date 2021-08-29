#ifndef PICO_LINEAR_ENCODER_C
#define PICO_LINEAR_ENCODER_C

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct linear_encoder_t {
  uint8_t pin;
  uint8_t value;
  double max_raw, min_raw;
  uint8_t cycles_till_change, required_repeats;
  long long int loop_delay;
  void (*onchange)(struct linear_encoder_t *encoder);
} linear_encoder_t;

double linear_encoder_raw_value(linear_encoder_t *encoder) {
  adc_select_input(encoder->pin - 26);
  double raw = (double)adc_read();
  if (raw > encoder->max_raw) return encoder->max_raw;
  if (raw < encoder->min_raw) return encoder->min_raw;
  return raw;
}

uint8_t linear_encoder_value(linear_encoder_t *encoder) {
  double raw = linear_encoder_raw_value(encoder);
  double track = encoder->max_raw - encoder->min_raw;
  double pos = raw - encoder->min_raw;
  double value = round((pos/track) * 255);
  return (uint8_t)(value > 255 ? 255 : value);
}

void linear_encoder_tick(linear_encoder_t *encoder) {
  uint8_t value = linear_encoder_value(encoder);
  if (value == encoder->value) {
    encoder->cycles_till_change = encoder->required_repeats;
  } else if (encoder->cycles_till_change < 1) {
    encoder->cycles_till_change = encoder->required_repeats;
    encoder->value = value;
    encoder->onchange(encoder);
  } else {
    encoder->cycles_till_change--;
  }
}

long long int handle_linear_encoder_alarm(long int a, void *p) {
  linear_encoder_t *encoder = (linear_encoder_t *)p;
  linear_encoder_tick(encoder);
  return encoder->loop_delay;
}

linear_encoder_t * create_encoder(uint8_t pin, void (*onchange)(linear_encoder_t *encoder)) {
  linear_encoder_t *encoder = malloc(sizeof(linear_encoder_t));
  adc_init();
  adc_gpio_init(pin); // Make sure GPIO pin is high-impedance, no pullups etc
  encoder->pin = pin;
  encoder->max_raw = 4086;
  encoder->min_raw = 15;
  encoder->value = linear_encoder_value(encoder);
  encoder->onchange = onchange;
  encoder->required_repeats = 10;
  encoder->cycles_till_change = encoder->required_repeats;
  encoder->loop_delay = 10000; // 10ms
  add_alarm_in_us(encoder->loop_delay, handle_linear_encoder_alarm, encoder, true);
  return encoder;
}

#endif

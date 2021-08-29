# pico-linear-encoder.c

Enables you to use a linear potentiometer as if it was a small cheap linear encoder.

## Installation

Install with [clib(1)](https://github.com/clibs/clib):

```sh
$ clib install jkroso/pico-linear-encoder.c
```

## Api

- `linear_encoder_t create_linear_encoder(pin, onchange)`

Pin map:

| Pico     | Slider |
|---------:|:-------|
|GPIO 26-29| Pin 2  |
|Vref      | Pin 1  |
|Ground    | Pin 3  |

## Example

```c
#include "pico-linear-encoder/linear-encoder.c"

void onchange(linear_encoder_t *encoder) {
  printf("onchange: %d\n", encoder->value);
}

int main() {
  stdio_init_all();
  linear_encoder_t *encoder = create_encoder(26, onchange);
  while (true) tight_loop_contents(); // everything is interrupt driven
  return 0;
}
```

#include "pico/stdlib.h"
#include <stdio.h>

#define LED_BLUE 11

void ligar_azul(char expected) {
  if(expected == 'C'){
    gpio_put(LED_BLUE, true);
    printf("LED Azul Ligado.");
    sleep_ms(333);
    printf(".");
    sleep_ms(333);
    printf(".\n");
    sleep_ms(333);
    gpio_put(LED_BLUE, false);
  }
}
void led_azul_morse(char expected) {
  //Flash Azul mostrando a letra C em morse
  if (expected == 'C'){
    gpio_put(LED_BLUE, true);
    printf("-");
    sleep_ms(800);
    gpio_put(LED_BLUE, false);
    sleep_ms(125);
    gpio_put(LED_BLUE, true);
    printf(".");
    sleep_ms(200);
    gpio_put(LED_BLUE, false);
    sleep_ms(125);
    gpio_put(LED_BLUE, true);
    printf("-");
    sleep_ms(800);
    gpio_put(LED_BLUE, false);
    sleep_ms(125);
    gpio_put(LED_BLUE, true);
    printf(".\n");
    sleep_ms(200);
    gpio_put(LED_BLUE, false);
    sleep_ms(250);
  }
}
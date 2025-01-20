/**
 Botão de SOS com LEDs e Buzzer
**/

#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração do pino do LED vermelho
const uint led_pin_red = 12;

// Configuração do pino do buzzer
#define BUZZER_PIN 21

// Configuração da frequência do buzzer (em Hz)
#define BUZZER_FREQUENCY 1000

// Definição de uma função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin)
{
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

// Definição de uma função para emitir um beep com duração especificada
void beep(uint pin, uint duration_ms, uint pausa)
{
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048);

    gpio_put(led_pin_red, 1); // Liga o LED vermelho

    // Temporização
    sleep_ms(duration_ms);

    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);

    gpio_put(led_pin_red, 0); // Desliga o LED vermelho

    // Pausa entre os beeps
    sleep_ms(pausa); // Pausa de 100ms
}

int main()
{
    // Configuração do LED vermelho como saída
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    // Configuração do GPIO para o botão como entrada com pull-up
    const uint BUTTON_PIN = 5; // Pino do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração do GPIO para o buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    // Inicializar o PWM no pino do buzzer
    pwm_init_buzzer(BUZZER_PIN);
    while (true)
    {
        // Verifica o estado do botão
        if (gpio_get(BUTTON_PIN) == 0)
        { // Botão pressionado (nível lógico baixo)
            printf("Button pressed\n");
            // LEDs do SOS
            beep(BUZZER_PIN, 200, 125); // Bipe de 200ms
            beep(BUZZER_PIN, 200, 125); // Bipe de 200ms
            beep(BUZZER_PIN, 200, 250); // Bipe de 200ms

            beep(BUZZER_PIN, 800, 125); // Bipe de 800ms
            beep(BUZZER_PIN, 800, 125); // Bipe de 800ms
            beep(BUZZER_PIN, 800, 250); // Bipe de 800ms

            beep(BUZZER_PIN, 200, 125); // Bipe de 200ms
            beep(BUZZER_PIN, 200, 125); // Bipe de 200ms
            beep(BUZZER_PIN, 200, 250); // Bipe de 200ms
        }
    }
}
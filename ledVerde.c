// CÓDIGO PARA ACENDER O LED VERDE AO SER PRECIONADA A TECLA B NO TECLADO

#include <stdio.h>
#include "pico/stdlib.h"

#define LED_GREEN 10 // Pino conectado ao LED verde

const uint8_t colunas[4] = {1, 2, 3, 4}; // Pinos das colunas do teclado matricial
const uint8_t linhas[4] = {5, 6, 7, 8};  // Pinos das linhas do teclado matricial

const char teclado[4][4] = 
{
    {'1', '2', '3', 'A'}, 
    {'4', '5', '6', 'B'}, 
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para configurar o LED verde
void configurar_led_verde() 
{
    gpio_init(LED_GREEN);           // Inicializa o pino do LED verde
    gpio_set_dir(LED_GREEN, GPIO_OUT); // Define o pino como saída
    gpio_put(LED_GREEN, false);     // Inicializa o LED apagado
}

// Função para acender o LED verde
void acender_led_verde() 
{
    gpio_put(LED_GREEN, true);  // Acende o LED verde
    sleep_ms(1000);
    gpio_put(LED_GREEN, false);  // Apaga o LED verde

}

char leitura_teclado();

int main() 
{
    stdio_init_all();
    configurar_led_verde(); // Configura o LED verde

    // Configuração dos pinos das colunas como saídas digitais
    for (int i = 0; i < 4; i++) 
    {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_OUT);
        gpio_put(colunas[i], 1); // Inicializa todas as colunas como alto
    }

    // Configuração dos pinos das linhas como entradas digitais
    for (int i = 0; i < 4; i++) 
    {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_IN);
        gpio_pull_up(linhas[i]); // Habilita pull-up para as linhas
    }

    while (true) 
    {
        char tecla = leitura_teclado();

        if (tecla != 'n') // Só processa se uma tecla foi pressionada
        {
            printf("Tecla pressionada: %c\n", tecla);

            // Switch-case para executar a ação ao pressionar uma tecla
            switch (tecla) 
            {
                case 'B': // Acende o LED verde ao pressionar a tecla B
                    acender_led_verde();
                    break;

                default:
                    gpio_put(LED_GREEN, false); // Apaga o LED verde se outra tecla for pressionada
                    break;
            }
        }

        sleep_ms(200); // Pausa antes da próxima leitura
    }

    return 0;
}

// Função para ler o teclado matricial
char leitura_teclado() 
{
    char numero = 'n'; // Valor padrão para quando nenhuma tecla for pressionada

    // Desliga todas as colunas
    for (int i = 0; i < 4; i++) 
    {
        gpio_put(colunas[i], 1);
    }

    for (int coluna = 0; coluna < 4; coluna++) 
    {
        // Ativa a coluna atual
        gpio_put(colunas[coluna], 0);

        for (int linha = 0; linha < 4; linha++) 
        {
            // Verifica se a linha está ativa
            if (gpio_get(linhas[linha]) == 0) 
            {
                numero = teclado[linha][coluna]; // Mapeia a tecla pressionada

                // Aguarda a tecla ser liberada (debounce)
                while (gpio_get(linhas[linha]) == 0) 
                {
                    sleep_ms(10);
                }
                break; // Sai do laço após detectar a tecla
            }
        }

        // Desativa a coluna atual
        gpio_put(colunas[coluna], 1);

        if (numero != 'n') // Sai do laço de colunas se uma tecla foi detectada
        {
            break;
        }
    }

    return numero; // Retorna a tecla pressionada
}

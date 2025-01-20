#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos usados (exemplo)
#define ROW1 3      // Linha onde ficam as teclas 4,5,6,B
#define COL0 6      // Coluna referente à tecla 4
#define COL1 7      // Coluna referente à tecla 5
#define COL2 8      // Coluna referente à tecla 6
#define COL3 9      // Coluna referente à tecla B (não usado aqui, mas declarado)

int main() {
    // Inicializa a saída USB para debug (printf)
    stdio_init_all();
    printf("Lendo teclas 4,5,6 do Keypad...\n");

    // Configura a linha R1 como saída
    gpio_init(ROW1);
    gpio_set_dir(ROW1, GPIO_OUT);
    // Coloca a linha em nível alto inicialmente (desativada)
    gpio_put(ROW1, 1);

    // Configura as colunas como entrada com pull-up
    gpio_init(COL0);
    gpio_set_dir(COL0, GPIO_IN);
    gpio_pull_up(COL0);

    gpio_init(COL1);
    gpio_set_dir(COL1, GPIO_IN);
    gpio_pull_up(COL1);

    gpio_init(COL2);
    gpio_set_dir(COL2, GPIO_IN);
    gpio_pull_up(COL2);

    gpio_init(COL3);
    gpio_set_dir(COL3, GPIO_IN);
    gpio_pull_up(COL3);

    while (true) {
        // Ativa a linha R1 colocando em nível baixo
        gpio_put(ROW1, 0);

        // Pequeno atraso para estabilizar
        sleep_us(5);

        // Lê as colunas (0 = pressionado)
        bool c0_pressed = (gpio_get(COL0) == 0);
        bool c1_pressed = (gpio_get(COL1) == 0);
        bool c2_pressed = (gpio_get(COL2) == 0);
        // c3_pressed corresponderia à tecla B (não é foco aqui)

        // Verifica cada coluna
        if (c0_pressed) {
            printf("Tecla 4 pressionada!\n");
            sleep_ms(250); // para evitar repetição rápida
        }
        if (c1_pressed) {
            printf("Tecla 5 pressionada!\n");
            sleep_ms(250);
        }
        if (c2_pressed) {
            printf("Tecla 6 pressionada!\n");
            sleep_ms(250);
        }

        // Desativa a linha (volta ao nível alto)
        gpio_put(ROW1, 1);

        // Aguarda um pouquinho
        sleep_ms(100);
    }

    return 0;
}

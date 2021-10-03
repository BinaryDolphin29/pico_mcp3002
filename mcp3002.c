#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/types.h"
#include "hardware/spi.h"

#define SCK  6
#define MISO 4
#define MOSI 7
#define CS 5

const uint8_t const configBits[2] = {0x68, 0x00};

void setup() {
    stdio_init_all();
    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);

    spi_init(spi0, 8000000);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_put(CS, 1);
}

int main() {
    setup();

    while (1) {
        uint8_t buf[2];
        gpio_put(CS, 0);
        spi_read_blocking(spi0, *configBits, buf, 2);

        uint16_t analogValue = ((buf[0] & 0b00000011) << 8) | buf[1];
        printf("%04d (MSB 0x%02x / LSB 0x%02x)\n", analogValue, buf[0], buf[1]);

        gpio_put(CS, 1);
        sleep_ms(100);
    }
}
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "lora.h"

lora_config_t default_config = {
    .m0 = 4,
    .m1 = 5,
    .tx = 1,
    .rx = 2,
    .baudrate = BAUDRATE_9600,
    .speed = MEDIUM,
    .uart_id = 0,
};

void lora_init(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    gpio_init(config->m0);
    gpio_init(config->m1);
    gpio_init(config->tx);
    gpio_init(config->rx);

    gpio_set_dir(config->m0, GPIO_OUT);
    gpio_set_dir(config->m1, GPIO_OUT);
    gpio_set_dir(config->tx, GPIO_OUT);
    gpio_set_dir(config->rx, GPIO_IN);

    gpio_put(config->m0, 0);
    gpio_put(config->m1, 0);

    uart_init(config->uart_id > 0 ? uart1 : uart0, config->baudrate);
    gpio_set_function(config->tx, GPIO_FUNC_UART);
    gpio_set_function(config->rx, GPIO_FUNC_UART);

    sleep_ms(2000);

    lora_reset(config);
}

void lora_reset(lora_config_t *config)
{
    lora_sleep_mode(config); // set sleep mode to reset module

    char command_hex = 0xC4;
    char command[3] = {command_hex, command_hex, command_hex};

    uart_puts(config->uart_id > 0 ? uart1 : uart0, command); //reset module

    sleep_ms(2000);

    lora_normal_mode(config); // set normal mode
}

void lora_deinit(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    uart_deinit(config->uart_id > 0 ? uart1 : uart0);

    gpio_deinit(config->m0);
    gpio_deinit(config->m1);
    gpio_deinit(config->tx);
    gpio_deinit(config->rx);
}

void lora_sleep_mode(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    gpio_put(config->m0, 1);
    gpio_put(config->m1, 1);
}

void lora_normal_mode(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    gpio_put(config->m0, 0);
    gpio_put(config->m1, 0);
}

void lora_powersave_mode(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    gpio_put(config->m0, 1);
    gpio_put(config->m1, 0);
}

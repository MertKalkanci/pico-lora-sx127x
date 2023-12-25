#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "lora.h"

int baudrate_to_int(lora_baudrate_t baudrate)
{
    switch (baudrate)
    {
    case BAUDRATE_1200:
        return 1200;
    case BAUDRATE_2400:
        return 2400;
    case BAUDRATE_4800:
        return 4800;
    case BAUDRATE_9600:
        return 9600;
    case BAUDRATE_19200:
        return 19200;
    case BAUDRATE_38400:
        return 38400;
    case BAUDRATE_57600:
        return 57600;
    case BAUDRATE_115200:
        return 115200;
    default:
        return 9600;
    }
}

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

    uart_init(config->uart_id > 0 ? uart1 : uart0, 9600); //while resetting the module in sleep mode, the baudrate is 9600
    gpio_set_function(config->tx, GPIO_FUNC_UART);
    gpio_set_function(config->rx, GPIO_FUNC_UART);

    sleep_ms(1000);

    lora_reset(config);

    sleep_ms(1000);

    char configration_hex = config->speed + (config->baudrate + 1) * 8;
    char *configration_command = malloc(5 * sizeof(char));
    configration_command = strcat("SPED", &configration_hex);

    uart_puts(config->uart_id > 0 ? uart1 : uart0, configration_command); // set speed and baudrate on lora module

    uart_set_baudrate(config->uart_id > 0 ? uart1 : uart0, baudrate_to_int(config->baudrate)); // set baudrate on uart pins
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

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
    .aux = 6 ,
    .baudrate = BAUDRATE_9600,
    .speed = MEDIUM,
    .uart_id = 0,
    .addres_low = 0x00,
    .addres_high = 0xFF,
    .transparent_mode = false,
    .config_mode = NOT_SAVE_AFTER_POWER_OFF
};

void lora_blocking_wait_aux(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    while (gpio_get(config->aux) == 0)
    {
        sleep_ms(10);
    }
} 

void lora_reset(lora_config_t *config)
{
    lora_sleep_mode(config); // set sleep mode to reset module

    char command_hex = 0xC4;
    char command[3] = {command_hex, command_hex, command_hex};

    uart_puts(config->uart_id > 0 ? uart1 : uart0, command); //reset module

    lora_blocking_wait_aux(config); // wait for aux pin to go high

    lora_normal_mode(config); // set normal mode
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

    lora_blocking_wait_aux(config); // wait for aux pin to go high
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

void lora_configure(lora_config_t *config)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    lora_sleep_mode(config); // set sleep mode to configure module

    uart_set_baudrate(config->uart_id > 0 ? uart1 : uart0, 9600); // set baudrate on uart pins for configuration

    char *configration_command = malloc(6);

    configration_command[0] = (char*)config->config_mode;
    configration_command[1] = (char*)config->addres_high;
    configration_command[2] = (char*)config->addres_low;
    configration_command[3] = (char*)(config->speed + config->baudrate * 8);
    configration_command[4] = {0x00}; // set to 0x00 for default channel Will add channel configuration later
    configration_command[5] = (char*)(128 * config->transparent_mode + 64 + 4); 
    // set trqansparent mode and set IO drive mode, wireless wake-up time, FEC switch, transmission power, and air wake-up time to default values

    uart_puts(config->uart_id > 0 ? uart1 : uart0, configration_command); // set speed and baudrate on lora module
    uart_set_baudrate(config->uart_id > 0 ? uart1 : uart0, baudrate_to_int(config->baudrate)); // set baudrate on uart pins

    lora_blocking_wait_aux(config); // wait for aux pin to go high

    lora_normal_mode(config); // set normal mode
}

void lora_set_address(lora_config_t *config, uint8_t low, uint8_t high)
{
    if (config == NULL)
    {
        config = &default_config;
    }

    config->addres_low = low;
    config->addres_high = high;

    lora_configure(config);
}

void lora_send(const void *data, size_t size)
{

}

void lora_receive(const void *data, size_t size)
{

}

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
    gpio_init(config->aux);

    gpio_set_dir(config->m0, GPIO_OUT);
    gpio_set_dir(config->m1, GPIO_OUT);
    gpio_set_dir(config->tx, GPIO_OUT);
    gpio_set_dir(config->rx, GPIO_IN);
    gpio_set_dir(config->aux, GPIO_IN);

    uart_init(config->uart_id > 0 ? uart1 : uart0, 9600); //while resetting the module in sleep mode, the baudrate is 9600
    gpio_set_function(config->tx, GPIO_FUNC_UART);
    gpio_set_function(config->rx, GPIO_FUNC_UART);

    lora_normal_mode(config); // set normal mode

    lora_reset(config);

    lora_configure(config);
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

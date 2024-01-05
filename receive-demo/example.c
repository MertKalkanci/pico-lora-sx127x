#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "lora.h"

lora_config_t my_lora_config = {
    .aux = 9,
    .tx = 10,
    .rx = 11,
    .m0 = 15,
    .m1 = 14,
    .baudrate = BAUDRATE_9600,
    .speed = MEDIUM,
    .uart_id = 1,
    .addres_low = 0x00,
    .addres_high = 0xFF,
    .transparent_mode = false,
    .config_mode = NOT_SAVE_AFTER_POWER_OFF
};

typedef struct simple_message {
    uint8_t id;
    uint8_t data[10];
} simple_message_t;

int main ()
{
    lora_init(&my_lora_config);

    simple_message_t *message_received = malloc(sizeof(simple_message_t));

    while (1) {
        lora_receive_blocking(&my_lora_config, message_received, sizeof(simple_message_t));

        printf("Message received with ID: %d\n", message_received->id);
        printf("Data received: ");

        for (int i = 0; i < 10; i++) {
            printf("%d, ", message_received->data[i]);
            }
    }
}
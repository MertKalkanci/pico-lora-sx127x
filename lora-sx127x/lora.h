#ifndef LORA_H
#define LORA_H

typedef enum lora_transaction_speed {
    VERY_SLOW=0,
    SLOW=1,
    MEDIUM=2,
    FAST=3,
    VERY_FAST=4,
    ULTRA_FAST=5
} lora_transaction_speed_t;

typedef enum lora_baudrate {
    BAUDRATE_1200=0,
    BAUDRATE_2400=1,
    BAUDRATE_4800=2,
    BAUDRATE_9600=3,
    BAUDRATE_19200=4,
    BAUDRATE_38400=5,
    BAUDRATE_57600=6,
    BAUDRATE_115200=7
} lora_baudrate_t;

int baudrate_to_int(lora_baudrate_t baudrate);

typedef struct lora_config  {
    uint8_t m0;
    uint8_t m1;
    uint8_t tx;
    uint8_t rx;
    uint8_t uart_id;
    lora_baudrate_t baudrate;
    lora_transaction_speed_t speed;
} lora_config_t;

void lora_init(lora_config_t *config);

void lora_reset(lora_config_t *config);

void lora_deinit(lora_config_t *config);

void lora_send_raw(uint8_t *data);

void lora_send(struct stream data);

void lora_receive(struct stream *data, uint8_t len);

void lora_sleep_mode(lora_config_t *config);

void lora_normal_mode(lora_config_t *config);

void lora_powersave_mode(lora_config_t *config);

#endif
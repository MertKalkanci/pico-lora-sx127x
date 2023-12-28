#ifndef LORA_H
#define LORA_H

typedef enum config_mode { 
    NOT_SAVE_AFTER_POWER_OFF=0xC2 ,
    SAVE_AFTER_POWER_OFF=0xC0
} config_mode_t; // set configuration mode 0xC2 to not save configuration after power off 0xC0 to save configuration after power off


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
    uint8_t addres_low;
    uint8_t addres_high;
    bool transparent_mode;
    config_mode_t config_mode;
} lora_config_t;

void lora_init(lora_config_t *config);

void lora_reset(lora_config_t *config);

void lora_deinit(lora_config_t *config);

void lora_set_address(lora_config_t *config, uint8_t low, uint8_t high);

void lora_configure(lora_config_t *config);

void lora_send(const void *data, size_t size);

void lora_receive(const void *data, size_t size);

void lora_sleep_mode(lora_config_t *config);

void lora_normal_mode(lora_config_t *config);

void lora_powersave_mode(lora_config_t *config);

void lora_wait_aux(lora_config_t *config);

#endif
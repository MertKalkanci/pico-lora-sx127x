#ifndef LORA_H
#define LORA_H

#define BAUDRATE_CONFIG 8

#define TRANSMISSION_CHANNEL_DEFAULT 0x00

#define TRANSPARENT_MODE 128

#define IO_DRIVE_MODE_DEFAULT 64

#define WIRELESS_WAKE_UP_TIME_DEFAULT 0
#define WIRELESS_WAKEUP_TIME_250 0
#define WIRELESS_WAKEUP_TIME_500 8
#define WIRELESS_WAKEUP_TIME_750 16
#define WIRELESS_WAKEUP_TIME_1000 24
#define WIRELESS_WAKEUP_TIME_1250 32
#define WIRELESS_WAKEUP_TIME_1500 40
#define WIRELESS_WAKEUP_TIME_1750 48
#define WIRELESS_WAKEUP_TIME_2000 56

#define FEC_SWITCH_ON 4
#define FEC_SWITCH_OFF 0
#define FEC_SWITCH_DEFAULT 4

#define TRANSMISSION_POWER_DEFAULT 0
#define TRANSMISSON_POWER_HIGH 0
#define TRANSMISSON_POWER_MEDIUM 1
#define TRANSMISSON_POWER_LOW 2

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

typedef struct lora_config  {
    uint8_t m0;
    uint8_t m1;
    uint8_t tx;
    uint8_t rx;
    uint8_t aux;
    uint8_t uart_id;
    lora_baudrate_t baudrate;
    lora_transaction_speed_t speed;
    uint8_t addres_low;
    uint8_t addres_high;
    bool transparent_mode;
    config_mode_t config_mode;
} lora_config_t;

int baudrate_to_int(lora_baudrate_t baudrate);

void lora_blocking_wait_aux(const lora_config_t *config);

void lora_reset(lora_config_t *config);

void lora_sleep_mode(lora_config_t *config);

void lora_normal_mode(lora_config_t *config);

void lora_powersave_mode(lora_config_t *config);

void lora_configure(lora_config_t *config);

void lora_set_address(lora_config_t *config, uint8_t low, uint8_t high);

void lora_pad_data(char *restrict data, size_t size);

void lora_send(const lora_config_t *config, const void *data, size_t size);

void lora_receive(const lora_config_t *config, void *data, size_t size);

void lora_init(lora_config_t *config);

void lora_deinit(lora_config_t *config);

#endif
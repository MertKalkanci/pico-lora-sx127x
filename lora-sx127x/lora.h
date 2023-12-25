typedef enum lora_transaction_speed {
    VERY_SLOW,
    SLOW,
    MEDIUM,
    FAST,
    VERY_FAST,
    ULTRA_FAST
} lora_transaction_speed_t;

typedef enum lora_baudrate {
    BAUDRATE_1200=1200,
    BAUDRATE_2400=2400,
    BAUDRATE_4800=4800,
    BAUDRATE_9600=9600,
    BAUDRATE_19200=19200,
    BAUDRATE_38400=38400,
    BAUDRATE_57600=57600,
    BAUDRATE_115200=115200
} lora_baudrate_t;

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

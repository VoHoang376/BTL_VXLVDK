#include "dht20.h"

static I2C_HandleTypeDef *dht_i2c = NULL;
static DHT20_Data_t current_data = {0.0f, 0.0f, 0};

// Trạng thái nội bộ để đọc non-blocking
typedef enum {
    DHT_STATE_IDLE = 0,
    DHT_STATE_TRIGGER,
    DHT_STATE_WAIT_MEASURE
} DHT20_State_t;

static DHT20_State_t dht_state = DHT_STATE_IDLE;
static uint8_t idle_counter = 0;

// Kiểm tra CRC8 theo datasheet DHT20 (đa thức 0x31)
static uint8_t dht20_check_crc(uint8_t *data, uint8_t len) {
    uint8_t crc = 0xFF;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

void dht20_init(I2C_HandleTypeDef *hi2c) {
    dht_i2c = hi2c;
    HAL_Delay(100); // Chờ cảm biến ổn định sau cấp nguồn (chỉ chạy 1 lần lúc init)

    uint8_t status = 0;
    uint8_t cmd = 0x71;
    HAL_I2C_Master_Transmit(dht_i2c, DHT20_I2C_ADDR, &cmd, 1, 50);
    HAL_I2C_Master_Receive(dht_i2c, DHT20_I2C_ADDR, &status, 1, 50);

    // Nếu bit[3] != 1, cần reset thanh ghi hiệu chuẩn theo datasheet
    if ((status & 0x18) != 0x18) {
        uint8_t init_regs[3] = {0x1B, 0x1C, 0x1E};
        for (int i = 0; i < 3; i++) {
            uint8_t reset_cmd[3] = {init_regs[i], 0x00, 0x00};
            HAL_I2C_Master_Transmit(dht_i2c, DHT20_I2C_ADDR, reset_cmd, 3, 50);
            HAL_Delay(5);
        }
    }
    dht_state = DHT_STATE_TRIGGER;
}

// Gọi hàm này mỗi 100ms (10 ticks) trên Scheduler -> cứ 2 giây cập nhật 1 lần
void dht20_read_task(void) {
    if (dht_i2c == NULL) return;

    switch (dht_state) {
        case DHT_STATE_IDLE:
            idle_counter++;
            // Chờ đủ 19 chu kỳ x 100ms = 1.9s trước lần đo tiếp theo
            if (idle_counter >= 19) {
                idle_counter = 0;
                dht_state = DHT_STATE_TRIGGER;
            }
            break;

        case DHT_STATE_TRIGGER: {
            uint8_t trigger_cmd[3] = {0xAC, 0x33, 0x00};
            if (HAL_I2C_Master_Transmit(dht_i2c, DHT20_I2C_ADDR, trigger_cmd, 3, 20) == HAL_OK) {
                dht_state = DHT_STATE_WAIT_MEASURE;
            }
            break;
        }

        case DHT_STATE_WAIT_MEASURE: {
            // Đã trôi qua 100ms (> 80ms yêu cầu của DHT20), tiến hành đọc 7 byte (1 status + 5 data + 1 CRC)
            uint8_t rx_buf[7] = {0};
            if (HAL_I2C_Master_Receive(dht_i2c, DHT20_I2C_ADDR, rx_buf, 7, 20) == HAL_OK) {
                // Kiểm tra bit[7] == 0 (đã đo xong) và kiểm tra CRC
                if (((rx_buf[0] & 0x80) == 0) && (dht20_check_crc(rx_buf, 6) == rx_buf[6])) {
                    uint32_t raw_hum = ((uint32_t)rx_buf[1] << 12) |
                                       ((uint32_t)rx_buf[2] << 4)  |
                                       ((uint32_t)(rx_buf[3] >> 4));

                    uint32_t raw_temp = (((uint32_t)rx_buf[3] & 0x0F) << 16) |
                                        ((uint32_t)rx_buf[4] << 8)         |
                                        ((uint32_t)rx_buf[5]);

                    current_data.humidity = ((float)raw_hum / 1048576.0f) * 100.0f;
                    current_data.temperature = ((float)raw_temp / 1048576.0f) * 200.0f - 50.0f;
                    current_data.is_valid = 1;
                }
            }
            dht_state = DHT_STATE_IDLE;
            break;
        }
    }
}

DHT20_Data_t dht20_get_data(void) {
    return current_data;
}

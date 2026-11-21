#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include "main.h"
#include <stdint.h>

// Địa chỉ 7-bit của DHT20 là 0x38 -> 8-bit HAL là 0x70
#define DHT20_I2C_ADDR      (0x38 << 1)

typedef struct {
    float temperature;
    float humidity;
    uint8_t is_valid;
} DHT20_Data_t;

// Khởi tạo cảm biến (gọi 1 lần trong main trước khi vào scheduler)
void dht20_init(I2C_HandleTypeDef *hi2c);

// Task đọc cảm biến non-blocking (gọi định kỳ mỗi 100ms trên Scheduler)
void dht20_read_task(void);

// API cho lớp FSM/Display lấy dữ liệu mới nhất
DHT20_Data_t dht20_get_data(void);

#endif /* INC_DHT20_H_ */

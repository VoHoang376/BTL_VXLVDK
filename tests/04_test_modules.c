/* tests/04_test_modules.c
 * Hướng dẫn chạy test:
 * Include file này hoặc gọi test_dht20_lcd_init() trong main.c trước while(1)
 */
#include "main.h"
#include "scheduler.h"
#include "dht20.h"
#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

static void task_heartbeat_led(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

static void task_update_lcd_sensor(void) {
    DHT20_Data_t env = dht20_get_data();

    // Ghi đè trực tiếp tại tọa độ cố định thay vì gọi lcd_clear() để chống nhấp nháy
    lcd_set_cursor(0, 0);
    lcd_print_str("Temp: ");
    if (env.is_valid) {
        lcd_print_float(env.temperature, 1);
        lcd_print_str(" C   ");
    } else {
        lcd_print_str("--.- C   ");
    }

    lcd_set_cursor(1, 0);
    lcd_print_str("Humi: ");
    if (env.is_valid) {
        lcd_print_float(env.humidity, 1);
        lcd_print_str(" %   ");
    } else {
        lcd_print_str("--.- %   ");
    }
}

void test_dht20_lcd_setup(void) {
    // 1. Khởi tạo ngoại vi I2C
    lcd_init(&hi2c1);
    dht20_init(&hi2c1);

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print_str("CO3009 I2C Test");
    lcd_set_cursor(1, 0);
    lcd_print_str("Initializing...");

    // 2. Đăng ký các task vào Scheduler (tick = 10ms)
    SCH_Init();
    SCH_Add_Task(task_heartbeat_led, 0, 50);        // Nháy LED PA5 mỗi 500ms
    SCH_Add_Task(dht20_read_task, 10, 10);          // Máy trạng thái đọc DHT20 mỗi 100ms
    SCH_Add_Task(task_update_lcd_sensor, 50, 200);  // Cập nhật LCD mỗi 2000ms (2s)
}
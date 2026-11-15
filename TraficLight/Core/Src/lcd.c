#include "lcd.h"
#include <stdio.h>

static I2C_HandleTypeDef *lcd_i2c = NULL;

// Các bit điều khiển trên module PCF8574 (P0=RS, P1=RW, P2=EN, P3=Backlight)
#define LCD_RS          0x01
#define LCD_EN          0x04
#define LCD_BACKLIGHT   0x08

static void lcd_send_internal(uint8_t data, uint8_t flags) {
    if (lcd_i2c == NULL) return;

    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up | flags | LCD_BACKLIGHT | LCD_EN;
    data_arr[1] = up | flags | LCD_BACKLIGHT;
    data_arr[2] = lo | flags | LCD_BACKLIGHT | LCD_EN;
    data_arr[3] = lo | flags | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, data_arr, 4, 20);
}

static void lcd_send_cmd(uint8_t cmd) {
    lcd_send_internal(cmd, 0);
}

static void lcd_send_data(uint8_t data) {
    lcd_send_internal(data, LCD_RS);
}

void lcd_init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;

    // Chuỗi khởi tạo chuẩn HD44780 chế độ 4-bit (chạy 1 lần duy nhất lúc khởi động)
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20); // Chuyển sang giao tiếp 4-bit
    HAL_Delay(10);

    lcd_send_cmd(0x28); // 4-bit, 2 dòng, font 5x8
    HAL_Delay(1);
    lcd_send_cmd(0x08); // Tắt hiển thị
    HAL_Delay(1);
    lcd_send_cmd(0x01); // Xóa màn hình
    HAL_Delay(2);
    lcd_send_cmd(0x06); // Tự động dịch con trỏ sang phải
    HAL_Delay(1);
    lcd_send_cmd(0x0C); // Bật hiển thị, tắt con trỏ nhấp nháy
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
    // Lưu ý: Lệnh clear cần ~1.5ms để LCD thực thi, tránh gọi liên tục trong vòng lặp
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x80, 0xC0};
    if (row > 1) row = 1;
    if (col > 15) col = 15;
    lcd_send_cmd(row_offsets[row] + col);
}

void lcd_print_str(const char *str) {
    while (*str) {
        lcd_send_data((uint8_t)(*str));
        str++;
    }
}

void lcd_print_int(int32_t num) {
    char buf[12];
    snprintf(buf, sizeof(buf), "%ld", (long)num);
    lcd_print_str(buf);
}

void lcd_print_float(float num, uint8_t decimals) {
    char buf[16];
    if (num < 0) {
        lcd_print_str("-");
        num = -num;
    }
    int32_t int_part = (int32_t)num;
    if (decimals == 0) {
        snprintf(buf, sizeof(buf), "%ld", (long)int_part);
    } else {
        int32_t mult = 1;
        for (uint8_t i = 0; i < decimals; i++) mult *= 10;
        int32_t frac_part = (int32_t)((num - (float)int_part) * mult + 0.5f);
        if (frac_part >= mult) {
            int_part++;
            frac_part = 0;
        }
        if (decimals == 1) {
            snprintf(buf, sizeof(buf), "%ld.%01ld", (long)int_part, (long)frac_part);
        } else {
            snprintf(buf, sizeof(buf), "%ld.%02ld", (long)int_part, (long)frac_part);
        }
    }
    lcd_print_str(buf);
}

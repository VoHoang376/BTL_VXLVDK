#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include <stdint.h>

#define LCD_I2C_ADDR    (0x21 << 1)

void lcd_init(I2C_HandleTypeDef *hi2c);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print_str(const char *str);
void lcd_print_int(int32_t num);
void lcd_print_float(float num, uint8_t decimals);

#endif /* INC_LCD_H_ */

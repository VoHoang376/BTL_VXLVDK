#include "traffic_light.h"
#include "global.h"
#include "main.h"

// =================== TRAFFIC LIGHT 1 ===================
void set_Traffic_1_Red(void) {
    HAL_GPIO_WritePin(TRAFFIC1_PIN1_GPIO_Port, TRAFFIC1_PIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TRAFFIC1_PIN2_GPIO_Port, TRAFFIC1_PIN2_Pin, GPIO_PIN_SET);
}

void set_Traffic_1_Green(void) {
    HAL_GPIO_WritePin(TRAFFIC1_PIN1_GPIO_Port, TRAFFIC1_PIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TRAFFIC1_PIN2_GPIO_Port, TRAFFIC1_PIN2_Pin, GPIO_PIN_RESET);
}

void set_Traffic_1_Yellow(void) {
    HAL_GPIO_WritePin(TRAFFIC1_PIN1_GPIO_Port, TRAFFIC1_PIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRAFFIC1_PIN2_GPIO_Port, TRAFFIC1_PIN2_Pin, GPIO_PIN_SET);
}

// =================== TRAFFIC LIGHT 2 ===================
void set_Traffic_2_Red(void) {
    HAL_GPIO_WritePin(TRAFFIC2_PIN1_GPIO_Port, TRAFFIC2_PIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TRAFFIC2_PIN2_GPIO_Port, TRAFFIC2_PIN2_Pin, GPIO_PIN_SET);
}

void set_Traffic_2_Green(void) {
    HAL_GPIO_WritePin(TRAFFIC2_PIN1_GPIO_Port, TRAFFIC2_PIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TRAFFIC2_PIN2_GPIO_Port, TRAFFIC2_PIN2_Pin, GPIO_PIN_RESET);
}

void set_Traffic_2_Yellow(void) {
    HAL_GPIO_WritePin(TRAFFIC2_PIN1_GPIO_Port, TRAFFIC2_PIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRAFFIC2_PIN2_GPIO_Port, TRAFFIC2_PIN2_Pin, GPIO_PIN_SET);
}

void set_Traffic_1_Off(void) {
    HAL_GPIO_WritePin(TRAFFIC1_PIN1_GPIO_Port, TRAFFIC1_PIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRAFFIC1_PIN2_GPIO_Port, TRAFFIC1_PIN2_Pin, GPIO_PIN_RESET);
}

void set_Traffic_2_Off(void) {
    HAL_GPIO_WritePin(TRAFFIC2_PIN1_GPIO_Port, TRAFFIC2_PIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TRAFFIC2_PIN2_GPIO_Port, TRAFFIC2_PIN2_Pin, GPIO_PIN_RESET);
}

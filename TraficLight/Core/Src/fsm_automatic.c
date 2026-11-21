#include "fsm_automatic.h"
#include "traffic_light.h"
#include "global.h"

int auto_counter = 0;
static int tick_1s_counter = 0;

void fsm_automatic_run(void) {
    switch(status) {
        case INIT:
            status = AUTO_RED_GREEN;
            auto_counter = time_green;
            auto_counter = 3;
            tick_1s_counter = 0;
            break;

        case AUTO_RED_GREEN:
            set_Traffic_1_Red();
            set_Traffic_2_Green();

            auto_counter--;
            if (auto_counter <= 0) {
                status = AUTO_RED_YELLOW;
                auto_counter = time_yellow;
            tick_1s_counter++;
            if (tick_1s_counter >= 20) { // 20 x 50ms = 1s
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status = AUTO_RED_YELLOW;
                    auto_counter = 2;
                }
            }

            if (isButtonPressed(0)) {
                status = MAN_RED_GREEN;
            }
            break;

        case AUTO_RED_YELLOW:
            set_Traffic_1_Red();
            set_Traffic_2_Yellow();

            auto_counter--;
            if (auto_counter <= 0) {
                status = AUTO_GREEN_RED;
                auto_counter = time_green;
            tick_1s_counter++;
            if (tick_1s_counter >= 20) {
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status = AUTO_GREEN_RED;
                    auto_counter = 3;
                }
            }

            if (isButtonPressed(0)) {
                status = MAN_RED_GREEN;
            }
            break;

        case AUTO_GREEN_RED:
            set_Traffic_1_Green();
            set_Traffic_2_Red();

            auto_counter--;
            if (auto_counter <= 0) {
                status = AUTO_YELLOW_RED;
                auto_counter = time_yellow;
            tick_1s_counter++;
            if (tick_1s_counter >= 20) {
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status = AUTO_YELLOW_RED;
                    auto_counter = 2;
                }
            }

            if (isButtonPressed(0)) {
                status = MAN_RED_GREEN;
            }
            break;

        case AUTO_YELLOW_RED:
            set_Traffic_1_Yellow();
            set_Traffic_2_Red();

            auto_counter--;
            if (auto_counter <= 0) {
                status = AUTO_RED_GREEN;
                auto_counter = time_green;
            tick_1s_counter++;
            if (tick_1s_counter >= 20) {
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status = AUTO_RED_GREEN;
                    auto_counter = 3;
                }
            }

            if (isButtonPressed(0)) {
                status = MAN_RED_GREEN;
            }
            break;

        default:
            break;
    }
}

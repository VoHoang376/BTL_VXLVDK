#include "fsm_automatic.h"
#include "traffic_light.h"
#include "global.h"

int auto_counter = 0;
static int tick_1s_counter = 0;

void fsm_automatic_run(void) {
    // Chỉ chạy đèn tự động khi hệ thống đang ở MODE_NORMAL
    if (mode != MODE_NORMAL) {
        tick_1s_counter = 0;
        return;
    }

    switch (status_auto) {
        case AUTO_RED1_GREEN2:
            if (auto_counter <= 0) {
                auto_counter = time_green;
            }
            set_Traffic_1_Red();
            set_Traffic_2_Green();

            tick_1s_counter++;
            if (tick_1s_counter >= 20) { // 20 x 50ms = 1s
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status_auto = AUTO_RED1_YELLOW2;
                    auto_counter = time_yellow;
                }
            }
            break;

        case AUTO_RED1_YELLOW2:
            set_Traffic_1_Red();
            set_Traffic_2_Yellow();

            tick_1s_counter++;
            if (tick_1s_counter >= 20) {
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status_auto = AUTO_GREEN1_RED2;
                    auto_counter = time_green;
                }
            }
            break;

        case AUTO_GREEN1_RED2:
            set_Traffic_1_Green();
            set_Traffic_2_Red();

            tick_1s_counter++;
            if (tick_1s_counter >= 20) {
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status_auto = AUTO_YELLOW1_RED2;
                    auto_counter = time_yellow;
                }
            }
            break;

        case AUTO_YELLOW1_RED2:
            set_Traffic_1_Yellow();
            set_Traffic_2_Red();

            tick_1s_counter++;
            if (tick_1s_counter >= 20) {
                tick_1s_counter = 0;
                auto_counter--;
                if (auto_counter <= 0) {
                    status_auto = AUTO_RED1_GREEN2;
                    auto_counter = time_green;
                }
            }
            break;

        default:
            status_auto = AUTO_RED1_GREEN2;
            auto_counter = time_green;
            break;
    }
}

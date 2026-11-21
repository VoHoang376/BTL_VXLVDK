#include "fsm_tuning.h"
#include "traffic_light.h"

static int blink_counter = 0;
static int blink_state = 0;

void fsm_mode_switch(void) {
    if (isButtonPressed(0)) { // Nút 0: AUTO -> MANUAL -> TUN_GRN -> TUN_YEL -> AUTO
        mode++;
        if (mode > MODE_TUNE_YELLOW) {
            mode = MODE_NORMAL;

            if (time_red != (time_green + time_yellow)) {
                time_red = time_green + time_yellow;
            }

            status_auto = AUTO_RED1_GREEN2;
            auto_counter = time_green;
            set_Traffic_1_Red();
            set_Traffic_2_Green();
        }

        status_manual = MAN_RED_GREEN;
        temp_red = time_red;
        temp_green = time_green;
        temp_yellow = time_yellow;
        blink_counter = 0;
        blink_state = 0;
    }
}

void fsm_tuning_run(void) {
    if (mode != MODE_TUNE_GREEN && mode != MODE_TUNE_YELLOW) {
        return;
    }

    // Nhấp nháy LED 2Hz (đảo mỗi 250ms = 5 x 50ms)
    blink_counter++;
    if (blink_counter >= 5) {
        blink_counter = 0;
        blink_state = !blink_state;
    }

    switch (mode) {
        case MODE_TUNE_GREEN:
            if (blink_state) { set_Traffic_1_Green(); set_Traffic_2_Green(); }
            else             { set_Traffic_1_Off();   set_Traffic_2_Off(); }

            if (isButtonPressed(2)) { // Nút 2: -1s
                temp_green--;
                if (temp_green < 1) temp_green = 99;
            }
            if (isButtonPressed(3)) { // Nút 3: +1s
                temp_green++;
                if (temp_green > 99) temp_green = 1;
            }
            if (isButtonPressed(1)) { // Nút 1: SET
                time_green = temp_green;
                time_red = time_green + time_yellow;
            }
            break;

        case MODE_TUNE_YELLOW:
            if (blink_state) { set_Traffic_1_Yellow(); set_Traffic_2_Yellow(); }
            else             { set_Traffic_1_Off();    set_Traffic_2_Off(); }

            if (isButtonPressed(2)) { // Nút 2: -1s
                temp_yellow--;
                if (temp_yellow < 1) temp_yellow = 99;
            }
            if (isButtonPressed(3)) { // Nút 3: +1s
                temp_yellow++;
                if (temp_yellow > 99) temp_yellow = 1;
            }
            if (isButtonPressed(1)) { // Nút 1: SET
                time_yellow = temp_yellow;
                time_red = time_green + time_yellow;
            }
            break;

        default:
            break;
    }
}

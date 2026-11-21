#include "fsm_tuning.h"
#include "traffic_light.h"

void fsm_mode_switch(void) {
    if (isButton1Pressed()) {
        mode++;
        if (mode > MODE_TUNE_GREEN) {
            mode = MODE_NORMAL;

            if (time_red != (time_green + time_yellow)) {
                time_red = time_green + time_yellow;
            }

            status_auto = AUTO_RED1_GREEN2;
            set_Traffic_1_Red();
            set_Traffic_2_Green();
        }

        temp_red = time_red;
        temp_green = time_green;
        temp_yellow = time_yellow;
    }
}

void fsm_tuning_run(void) {
    switch (mode) {
        case MODE_TUNE_RED:
            if (isButton2Pressed()) {
                temp_red++;
                if (temp_red > 99) temp_red = 1;
            }

            if (isButton3Pressed()) {
                time_red = temp_red;
            }
            break;

        case MODE_TUNE_YELLOW:
            if (isButton2Pressed()) {
                temp_yellow++;
                if (temp_yellow > 99) temp_yellow = 1;
            }

            if (isButton3Pressed()) {
                time_yellow = temp_yellow;
            }
            break;

        case MODE_TUNE_GREEN:
            if (isButton2Pressed()) {
                temp_green++;
                if (temp_green > 99) temp_green = 1;
            }

            if (isButton3Pressed()) {
                time_green = temp_green;
            }
            break;

        default:
            break;
    }
}

#include "fsm_manual.h"
#include "traffic_light.h"
#include "global.h"

void fsm_manual_run(void) {
    switch(status) {
        case MAN_RED_GREEN:
            set_Traffic_1_Red();
            set_Traffic_2_Green();

            if (isButtonPressed(1)) status = MAN_RED_YELLOW;
            if (isButtonPressed(0)) status = INIT;
            break;

        case MAN_RED_YELLOW:
            set_Traffic_1_Red();
            set_Traffic_2_Yellow();

            if (isButtonPressed(1)) status = MAN_GREEN_RED;
            if (isButtonPressed(0)) status = INIT;
            break;

        case MAN_GREEN_RED:
            set_Traffic_1_Green();
            set_Traffic_2_Red();

            if (isButtonPressed(1)) status = MAN_YELLOW_RED;
            if (isButtonPressed(0)) status = INIT;
            break;

        case MAN_YELLOW_RED:
            set_Traffic_1_Yellow();
            set_Traffic_2_Red();

            if (isButtonPressed(1)) status = MAN_RED_GREEN;
            if (isButtonPressed(0)) status = INIT;
            break;

        default:
            break;
    }
}

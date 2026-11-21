#include "fsm_manual.h"
#include "traffic_light.h"
#include "global.h"

int status_manual = MAN_RED_GREEN;

void fsm_manual_run(void) {
    if (mode != MODE_MANUAL) return;

    switch (status_manual) {
        case MAN_RED_GREEN:
            set_Traffic_1_Red();
            set_Traffic_2_Green();
            if (isButtonPressed(1)) status_manual = MAN_RED_YELLOW;
            break;

        case MAN_RED_YELLOW:
            set_Traffic_1_Red();
            set_Traffic_2_Yellow();
            if (isButtonPressed(1)) status_manual = MAN_GREEN_RED;
            break;

        case MAN_GREEN_RED:
            set_Traffic_1_Green();
            set_Traffic_2_Red();
            if (isButtonPressed(1)) status_manual = MAN_YELLOW_RED;
            break;

        case MAN_YELLOW_RED:
            set_Traffic_1_Yellow();
            set_Traffic_2_Red();
            if (isButtonPressed(1)) status_manual = MAN_RED_GREEN;
            break;

        default:
            break;
    }
}

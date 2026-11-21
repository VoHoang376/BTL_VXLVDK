#ifndef GLOBAL_H
#define GLOBAL_H

#include "main.h"

#define MODE_NORMAL       1
#define MODE_MANUAL       2
#define MODE_TUNE_GREEN   3
#define MODE_TUNE_YELLOW  4

#define AUTO_RED1_GREEN2  10
#define AUTO_RED1_YELLOW2 11
#define AUTO_GREEN1_RED2  12
#define AUTO_YELLOW1_RED2 13

#define MAN_RED_GREEN     20
#define MAN_RED_YELLOW    21
#define MAN_GREEN_RED     22
#define MAN_YELLOW_RED    23

extern int mode;
extern int status_auto;
extern int status_manual;
extern int auto_counter;

extern int time_red;
extern int time_green;
extern int time_yellow;

extern int temp_red;
extern int temp_green;
extern int temp_yellow;

#endif

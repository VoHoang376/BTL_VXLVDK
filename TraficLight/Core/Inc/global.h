#ifndef GLOBAL_H
#define GLOBAL_H

#include "main.h"

#define MODE_NORMAL       1
#define MODE_TUNE_RED     2
#define MODE_TUNE_YELLOW  3
#define MODE_TUNE_GREEN   4

extern int mode;

extern int time_red;
extern int time_green;
extern int time_yellow;

extern int temp_red;
extern int temp_green;
extern int temp_yellow;

extern int status_auto;
#define AUTO_RED1_GREEN2  10
#define AUTO_RED1_YELLOW2 11
#define AUTO_GREEN1_RED2  12
#define AUTO_YELLOW1_RED2 13

#endif

#include <pebble.h>
#include "Globals.h"

tm* get_time();
void initLayoutTime();
void initLayoutDate();
void updateTime(struct tm* TimeInfos);
void eventTimeCatcher(struct tm* TimeInfos, TimeUnits Unit);

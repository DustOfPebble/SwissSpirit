#include <pebble.h>
#include "Globals.h"

#include "PhoneLinkView.h"
#include "DataExchanger.h"

tm* get_time();
void initLayoutClock();
void updateTime(struct tm* TimeInfos);
void eventTimeCatcher(struct tm* TimeInfos, TimeUnits Unit);

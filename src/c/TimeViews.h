#include <pebble.h>
#include "Globals.h"

#include "PhoneLinkView.h"
#include "DataExchanger.h"

tm* get_time();
void initLayoutClock();
void updateClock(struct tm* TimeInfos, TimeUnits Unit);
void drawClock(struct tm* TimeInfos);

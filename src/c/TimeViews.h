#include <pebble.h>
#include "Globals.h"

#include "PhoneLinkView.h"
#include "WeatherView.h"
#include "Receiver.h"

void initLayoutClock();
void updateClock(struct tm* TimeInfos, TimeUnits Unit);
void drawClock(struct tm* TimeInfos);

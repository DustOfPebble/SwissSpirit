#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "TimeViews.h"

//#################################################################################
void updateTime(struct tm* TimeInfos, TimeUnits Unit) { 
	// Create Time string to show
	char TimeString[5] = "00:00";
	snprintf(TimeString,sizeof(TimeString), "%02d:%02d", TimeInfos->tm_hour, TimeInfos->tm_min);
	
	// Writting Time string
	text_layer_set_text(timeDisplay, TimeString);

	// Marking as to be redrawn ...
	layer_mark_dirty(text_layer_get_layer(timeDisplay));
}

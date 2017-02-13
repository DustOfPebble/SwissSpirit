#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "TimeViews.h"

//#################################################################################
void updateTime(struct tm* TimeInfos, TimeUnits Unit) { 
	// Converting Value to text...
	char HoursText[] = "00";
	snprintf(HoursText, sizeof(HoursText), "%d", TimeInfos->tm_hour);		
	char MinutesText[] = "00";
	snprintf(MinutesText, sizeof(MinutesText), "%d", TimeInfos->tm_min);		
	
	// Create Time stringto show
	char TimeString[10];
	strcpy (TimeString,HoursText);
	strcat (TimeString,":");
	strcat (TimeString,MinutesText);
	
	// Writting Time string
	text_layer_set_text(timeDisplay, TimeString);

	// Marking as to be redrawn ...
	layer_mark_dirty(text_layer_get_layer(timeDisplay));
}

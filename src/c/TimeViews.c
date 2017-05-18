#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "TimeViews.h"
//#################################################################################
static char TimeString[6];
static char DateString[40];
static const char *Days[] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
static const char *Months[] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Août","Septembre","Octobre","Novembre","Décembre"};
static time_t TimeStampsUpdateClock;
//#################################################################################
void initLayoutClock(){
	time(&TimeStampsUpdateClock);

	text_layer_set_text_color(timeDisplay, TextColor);
	text_layer_set_text_alignment(timeDisplay,GTextAlignmentCenter);
	text_layer_set_font(timeDisplay,fonts_get_system_font(TIME_FONT));

	text_layer_set_text_color(dateDisplay, TextColor);
	text_layer_set_text_alignment(dateDisplay,GTextAlignmentLeft);
	text_layer_set_font(dateDisplay,fonts_get_system_font(DATE_FONT));
}
//#################################################################################
void drawClock(struct tm* TimeInfos) {

	// Create strings to show
	snprintf(TimeString,sizeof(TimeString), "%02d:%02d", TimeInfos->tm_hour, TimeInfos->tm_min);
	snprintf(DateString,sizeof(DateString), " %s\n %d %s", Days[TimeInfos->tm_wday],TimeInfos->tm_mday,Months[TimeInfos->tm_mon]);

	// Updating Layers
	text_layer_set_text(timeDisplay, TimeString);
	layer_mark_dirty(text_layer_get_layer(timeDisplay));

	text_layer_set_text(dateDisplay, DateString);
	layer_mark_dirty(text_layer_get_layer(dateDisplay));
}
//#################################################################################
void updateClock(struct tm* TimeInfos, TimeUnits Unit) {

	time(&TimeStampsUpdateClock);
	// Update every History ...
	updatePhoneLinkHistory();
	updateHeartBeatHistory();
	updateWeatherHistory();
	updateViewSelector();

	// Display need to be updated only every minute change
	drawClock(TimeInfos);
}

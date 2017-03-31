#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "TimeViews.h"
//#################################################################################
char TimeString[6];
char DateString[40];
const char *Days[] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char *Months[] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Août","Septembre","Octobre","Novembre","Décembre"};
//#################################################################################
void initLayoutTime(){
	text_layer_set_text_color(timeDisplay, TextColor);
	text_layer_set_text_alignment(timeDisplay,GTextAlignmentCenter);
	text_layer_set_font(timeDisplay,fonts_get_system_font(TIME_FONT));
}
//#################################################################################
void initLayoutDate(){
	text_layer_set_text_color(dateDisplay, TextColor);
	text_layer_set_text_alignment(dateDisplay,GTextAlignmentLeft);
	text_layer_set_font(dateDisplay,fonts_get_system_font(DATE_FONT));
}
//#################################################################################
void updateTime(struct tm* TimeInfos) {
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
void eventTimeCatcher(struct tm* TimeInfos, TimeUnits Unit) {
	updateTime(TimeInfos);
	updatePhoneLinkHistory();
	updateViewSelector();
}

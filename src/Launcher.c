#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "BasicView.h"
#include "SharedView.h"

Window *window = NULL;
Layer *timeDisplay = NULL;
Layer *dateDisplay = NULL;
Layer *batteryDisplay = NULL;
Layer *sharedDisplay = NULL;

GDrawCommandImage *icon_heart_beat = NULL;
GDrawCommandImage *icon_calls_missed = NULL;
GDrawCommandImage *icon_messages_unread = NULL;
GDrawCommandImage *icon_time_elapsed = NULL;

//#################################################################################
static void manage_phone_incomming_datas(DictionaryIterator *PhoneDatas, void *context) {
// Does this message contain a given value?
	Tuple *isHeartRate = dict_find(PhoneDatas, HeartBeatMeasure);
	if(isHeartRate)	{

	}
}
//#################################################################################
void Uudate_Time(struct tm* TimeInfos, TimeUnits Unit) {
  // Copying Hours and Minutes before asking for a redraw ..
  Secondes = TimeInfos->tm_sec;
  Minutes = TimeInfos->tm_min;
  Hours = TimeInfos->tm_hour;
  
  // Marking NeedleWindow as to be redrawn ...
  layer_mark_dirty(timeDisplay);
}
//#################################################################################
void loading(Window *window) {
	// Load graphic resources
	icon_heart_beat = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART_BEAT);
	icon_messages_unread = gdraw_command_image_create_with_resource(RESOURCE_ID_MESSAGES_UNREAD);
	icon_calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);
	icon_time_elapsed = gdraw_command_image_create_with_resource(RESOURCE_ID_TIME_ELAPSED);

	// Create Layers for content
	timeDisplay = layer_create(TimeFrame);
	dateDisplay = layer_create(DateFrame);
	batteryDisplay = layer_create(BatteryFrame);
	sharedDisplay = layer_create(SharedFrame);

	Layer *rootLayer = window_get_root_layer(window);
	layer_add_child(rootLayer, timeDisplay);
	layer_add_child(rootLayer, dateDisplay);
	layer_add_child(rootLayer, batteryDisplay);
	layer_add_child(rootLayer, sharedDisplay);

	layer_set_update_proc(timeDisplay, drawTime);
	layer_set_update_proc(dateDisplay, drawDate);
	layer_set_update_proc(batteryDisplay, drawBattery);
	layer_set_update_proc(sharedDisplay, drawShared);


	// Forcing a redraw every second ...
	tick_timer_service_subscribe(SECOND_UNIT, updateTime); 
}
//#################################################################################
void unLoading(Window *window) {
	gdraw_command_image_destroy(icon_heart_beat);
	gdraw_command_image_destroy(icon_messages_unread);
	gdraw_command_image_destroy(icon_calls_missed);
	gdraw_command_image_destroy(icon_time_elapsed);

	layer_destroy(layer);
}
//#################################################################################
int main(void) {
	// Loading and Applying settings
	window = window_create();
	window_set_background_color(window, GColorWhite);
	window_set_window_handlers(window, (WindowHandlers) { .load = loading, .unload = unLoading });
	window_stack_push(window, true);

	// Register to be notified about inbox received events
	app_message_register_inbox_received(manage_phone_incomming_datas);

	// Entering event loop until exit requested
	app_event_loop();

	// Exiting --> Clearing Memory
	window_destroy(window);
}

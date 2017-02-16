#include <pebble.h>

#include "Constants.h"
#include "Globals.h"

#include "TimeViews.h"
#include "BatteryView.h"
#include "SharedView.h"

//#################################################################################
Window *window = NULL;
TextLayer *timeDisplay = NULL;
TextLayer *dateDisplay = NULL;
Layer *batteryDisplay = NULL;
Layer *sharedDisplay = NULL;

GDrawCommandImage *icon_heart_beat = NULL;
GDrawCommandImage *icon_calls_missed = NULL;
GDrawCommandImage *icon_time_elapsed = NULL;
GDrawCommandImage *icon_phone_linked = NULL;
GDrawCommandImage *icon_phone_lost = NULL;

GColor TextColor;
GColor BackgroundColor;
//#################################################################################
static void manage_phone_incomming_datas(DictionaryIterator *PhoneDatas, void *context) {
// Does this message contain a given value?
	Tuple *isHeartRate = dict_find(PhoneDatas, HeartBeatMeasure);
	if(isHeartRate)	{	}
}
//#################################################################################
void loading(Window *window) {
	// Load graphic resources --> should be moved into corresponding module
	icon_heart_beat = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART_BEAT);
	icon_calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);
	icon_time_elapsed = gdraw_command_image_create_with_resource(RESOURCE_ID_TIME_ELAPSED);
	icon_phone_linked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	icon_phone_lost = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LOST);

	// Loading Basic shared colors Layers
	TextColor = GColorImperialPurple;
	BackgroundColor = GColorElectricBlue; // Not used 

	// Create Layers for content
	timeDisplay = text_layer_create(TimeFrame);
	initLayoutTime();	
	
	dateDisplay = text_layer_create(DateFrame);
	initLayoutDate();	
	
	batteryDisplay = layer_create(BatteryFrame);
	initLayoutBattery();
	
	sharedDisplay = layer_create(SharedFrame);

	Layer *rootLayer = window_get_root_layer(window);
	layer_add_child(rootLayer, text_layer_get_layer(timeDisplay));
	layer_add_child(rootLayer, text_layer_get_layer(dateDisplay));
	layer_add_child(rootLayer, batteryDisplay);
	layer_add_child(rootLayer, sharedDisplay);

	layer_set_update_proc(batteryDisplay, drawBattery);
	layer_set_update_proc(sharedDisplay, drawShared);

	// Subscribe to events services
	tick_timer_service_subscribe(MINUTE_UNIT, eventTimeCatcher); 
	battery_state_service_subscribe(updateBattery);

	// Force initial refresh on all layers 	
	updateTime(get_time());
	updateBattery(battery_state_service_peek()); 
}
//#################################################################################
void unLoading(Window *window) {
	// Destroy allocated graphic resources --> May be useless ...
	gdraw_command_image_destroy(icon_heart_beat);
	gdraw_command_image_destroy(icon_calls_missed);
	gdraw_command_image_destroy(icon_time_elapsed);
	gdraw_command_image_destroy(icon_phone_lost);
	gdraw_command_image_destroy(icon_phone_linked);
	
	// UnSubscribe to events services
	tick_timer_service_unsubscribe(); 
	battery_state_service_unsubscribe();


	layer_destroy(text_layer_get_layer(timeDisplay));
	layer_destroy(text_layer_get_layer(dateDisplay));
	layer_destroy(batteryDisplay);
	layer_destroy(sharedDisplay);
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

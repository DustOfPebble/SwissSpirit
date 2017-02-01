#include <pebble.h>

#include "Globals.h"

#include "Constants.h"
#include "HeartView.h"

// Milliseconds between frames

#define DELTA 100

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
static void trigRedraw(void *context)
{
// Draw the next frame
layer_mark_dirty(layer); 
}
//#################################################################################
static void manage_phone_incomming_datas(DictionaryIterator *PhoneDatas, void *context)
{
// Does this message contain a temperature value?
Tuple *isHeartRate = dict_find(PhoneDatas, HeartBeatMeasure);
if(isHeartRate)
{
// Start a beat sequence
app_timer_register(DELTA, trigRedraw, NULL);
}
}
//#################################################################################
void loading(Window *window)
{
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


// Continue the sequence
app_timer_register(DELTA, trigRedraw, NULL);
}
//#################################################################################
void unLoading(Window *window)
{
	gdraw_command_image_destroy(icon_heart_beat);
	gdraw_command_image_destroy(icon_messages_unread);
	gdraw_command_image_destroy(icon_calls_missed);
	gdraw_command_image_destroy(icon_time_elapsed);

layer_destroy(layer);
}
//#################################################################################
int main(void)
{
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

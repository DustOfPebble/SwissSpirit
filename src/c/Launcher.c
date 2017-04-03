#include <pebble.h>

#include "Constants.h"
#include "Globals.h"
#include "utils.h"

#include "TimeViews.h"
#include "BatteryView.h"
#include "HeartBeatView.h"
#include "PhoneLinkView.h"

#include "ViewSelector.h"
#include "DataExchanger.h"
//#################################################################################
Window *window = NULL;
TextLayer *timeDisplay = NULL;
TextLayer *dateDisplay = NULL;

Layer *batteryDisplay = NULL;
Layer *heartDisplay = NULL;
Layer *phoneDisplay = NULL;

GColor TextColor;
GColor BackgroundColor;

int SecondsSinceSensorUpdate;
int SecondsSinceDisconnection;
int SecondsSinceConnection;
int SecondsSinceTimeUpdate;
bool isPhoneConnected;
//#################################################################################
void loading(Window *window) {
	// Create Layers for content
	timeDisplay = text_layer_create(TimeFrame);
	dateDisplay = text_layer_create(DateFrame);
	initLayoutClock();

	batteryDisplay = layer_create(BatteryFrame);
	initLayoutBattery();

	phoneDisplay = layer_create(SharedFrame);
	layer_set_hidden(phoneDisplay,false);
	initLayoutPhoneLink();

	heartDisplay = layer_create(SharedFrame);
	layer_set_hidden(heartDisplay,true);
	initLayoutHeartBeat();

	Layer *rootLayer = window_get_root_layer(window);
	layer_add_child(rootLayer, text_layer_get_layer(timeDisplay));
	layer_add_child(rootLayer, text_layer_get_layer(dateDisplay));

	layer_add_child(rootLayer, batteryDisplay);
	layer_set_update_proc(batteryDisplay, drawBattery);

	layer_add_child(rootLayer, phoneDisplay);
	layer_set_update_proc(phoneDisplay, drawPhoneLink);

	layer_add_child(rootLayer, heartDisplay);
	layer_set_update_proc(heartDisplay, drawHeartBeat);

	// Subscribe to events services
	tick_timer_service_subscribe(SECOND_UNIT, updateClock);
	battery_state_service_subscribe(updateBattery);
	connection_service_subscribe((ConnectionHandlers) { .pebble_app_connection_handler = updatePhoneLink });

	// Force initial refresh on all layers
	updateBattery(battery_state_service_peek());
	updatePhoneLink(connection_service_peek_pebble_app_connection());
	drawClock(get_time());

}
//#################################################################################
void unLoading(Window *window) {
	// UnSubscribe to events services
	tick_timer_service_unsubscribe();
	battery_state_service_unsubscribe();

	// Destroy all Layers
	layer_destroy(text_layer_get_layer(timeDisplay));
	layer_destroy(text_layer_get_layer(dateDisplay));
	layer_destroy(batteryDisplay);
	layer_destroy(phoneDisplay);
	layer_destroy(heartDisplay);
}
//#################################################################################
int main(void) {
	// Shared vars initilization
	SecondsSinceSensorUpdate = -1; // Unknown
	SecondsSinceDisconnection = -1; // Unknown
	SecondsSinceConnection = -1; // Unknown
	isPhoneConnected=false; // Not Connected by default

	// Loading Basic shared colors Layers
	TextColor = GColorImperialPurple;
	BackgroundColor = GColorElectricBlue; // Not used

	// Loading and Applying settings
	window = window_create();
	window_set_background_color(window, GColorWhite);
	window_set_window_handlers(window, (WindowHandlers) { .load = loading, .unload = unLoading });
	window_stack_push(window, true);

	// Register to be notified about inbox received events
	app_message_register_inbox_received(received_done);
	app_message_register_inbox_dropped(received_dropped);
	app_message_register_outbox_failed(sent_failed);
	app_message_register_outbox_sent(sent_done);
	app_message_open(100, 100);

	// Entering event loop until exit requested
	app_event_loop();

	// Exiting --> Clearing Memory
	window_destroy(window);
}

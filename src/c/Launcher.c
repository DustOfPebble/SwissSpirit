#include <pebble.h>

#include "Constants.h"
#include "Globals.h"

#include "TimeViews.h"
#include "BatteryView.h"
#include "HeartBeatView.h"
#include "PhoneLinkView.h"

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
//#################################################################################
void loading(Window *window) {
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

	phoneDisplay = layer_create(SharedFrame);
	initLayoutPhoneLink();
	heartDisplay = layer_create(SharedFrame);
	initLayoutHeartBeat();

	Layer *rootLayer = window_get_root_layer(window);
	layer_add_child(rootLayer, text_layer_get_layer(timeDisplay));
	layer_add_child(rootLayer, text_layer_get_layer(dateDisplay));

	layer_add_child(rootLayer, batteryDisplay);
	layer_set_update_proc(batteryDisplay, drawBattery);

	layer_add_child(rootLayer, phoneDisplay);
	layer_set_update_proc(phoneDisplay, drawPhoneLink);

	layer_set_hidden(heartDisplay,true); // Waiting for a Beat info to show...
	layer_add_child(rootLayer, heartDisplay);
	layer_set_update_proc(heartDisplay, drawHeartMonitor);

	// Subscribe to events services
	tick_timer_service_subscribe(MINUTE_UNIT, eventTimeCatcher);
	battery_state_service_subscribe(updateBattery);
	connection_service_subscribe((ConnectionHandlers) { .pebble_app_connection_handler = updatePhoneLink });

	// Force initial refresh on all layers
	updateTime(get_time());
	updateBattery(battery_state_service_peek());
	updatePhoneLink(connection_service_peek_pebble_app_connection());
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

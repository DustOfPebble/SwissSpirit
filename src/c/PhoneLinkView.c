#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

#include "PhoneLinkView.h"
//#################################################################################
GDrawCommandImage *icon_phone_linked;
GDrawCommandImage *icon_phone_lost;

GDrawCommandImage *icon_calls_missed;
GDrawCommandImage *icon_time_elapsed;

static GPoint Origin;
tm* TimeStampsConnected;
tm* TimeStampsStartConnected;
//#################################################################################
void updatePhoneLinkHistory() {
	if (isPhoneConnected) TimeStampsConnected = get_time();
	SecondsSinceDisconnection = elapsed_seconds(TimeStampsConnected);
	SecondsSinceConnection = elapsed_seconds(TimeStampsStartConnected);
}
//#################################################################################
void updatePhoneLink(bool connected) {
	isPhoneConnected = connected;
	if (isPhoneConnected) TimeStampsStartConnected = get_time();
	updatePhoneLinkHistory();
	updateViewSelector();
	layer_mark_dirty(phoneDisplay);
}
//#################################################################################
void initLayoutPhoneLink() {
	icon_phone_linked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	icon_phone_lost = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LOST);

	GRect LayerBox = layer_get_bounds(phoneDisplay);
	GSize Box = gdraw_command_image_get_bounds_size(icon_phone_linked);
	Origin = GPoint(LayerBox.size.w/10,(LayerBox.size.h - Box.h)/2);

	icon_calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);
	icon_time_elapsed = gdraw_command_image_create_with_resource(RESOURCE_ID_TIME_ELAPSED);
}
//#################################################################################
void drawPhoneLink(Layer *frame, GContext* context) {
	gdraw_command_image_draw(context, icon_phone_linked, Origin);
	if (!isPhoneConnected) gdraw_command_image_draw(context, icon_phone_lost, Origin);
}




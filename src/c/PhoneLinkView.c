#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

#include "PhoneLinkView.h"
//#################################################################################
GDrawCommandImage *Phone;
GDrawCommandImage *isLinked;
GDrawCommandImage *isNotLinked;

GDrawCommandImage *calls_missed;

GDrawCommandImage *Chrono;
GDrawCommandSequence *ChronoElapsed;
//static int index;
static int maxIndex;

static GPoint Origin;
time_t TimeStampsLastConnected;
time_t TimeStampsStartConnected;
//#################################################################################
void updatePhoneLinkHistory() {
	if (isPhoneConnected) time(&TimeStampsLastConnected);
	SecondsSinceDisconnection = elapsed(TimeStampsLastConnected);
	SecondsSinceConnection = elapsed(TimeStampsStartConnected);
}
//#################################################################################
void updatePhoneLink(bool connectedState) {
	if (!isPhoneConnected && connectedState) time(&TimeStampsStartConnected);
	isPhoneConnected = connectedState;
	updatePhoneLinkHistory();
	layer_mark_dirty(phoneDisplay);
}
//#################################################################################
void initLayoutPhoneLink() {
	Phone = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE);
	isLinked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	isNotLinked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_NOT_LINKED);

	GRect LayerBox = layer_get_bounds(phoneDisplay);
	GSize Box = gdraw_command_image_get_bounds_size(Phone);
	Origin = GPoint(LayerBox.size.w/10,(LayerBox.size.h - Box.h)/2);

	calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);
	
	Chrono = gdraw_command_image_create_with_resource(RESOURCE_ID_CHRONO);
	ChronoElapsed = gdraw_command_sequence_create_with_resource(RESOURCE_ID_CHRONO_ELAPSED);
	maxIndex = gdraw_command_sequence_get_num_frames(ChronoElapsed);

	time(&TimeStampsLastConnected);
	time(&TimeStampsStartConnected);
}
//#################################################################################
void drawPhoneLink(Layer *frame, GContext* context) {
	gdraw_command_image_draw(context, Phone, Origin);
	if (isPhoneConnected)
	{
		gdraw_command_image_draw(context, isLinked, Origin);
	}
	else
	{
		gdraw_command_image_draw(context, isNotLinked, Origin);
	}
}




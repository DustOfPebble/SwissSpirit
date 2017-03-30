#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "PhoneLinkView.h"
//#################################################################################
GDrawCommandImage *icon_phone_linked;
GDrawCommandImage *icon_phone_lost;

GDrawCommandImage *icon_calls_missed;
GDrawCommandImage *icon_time_elapsed;

bool isPhoneConnected;
bool lastValue;
GPoint Origin;
//#################################################################################
void updatePhoneLink(bool connected) {
	isPhoneConnected = connected;
	layer_mark_dirty(phoneDisplay);
}
//#################################################################################
void updateDemo(int value) {
	lastValue = value;
	layer_mark_dirty(phoneDisplay);
}
//#################################################################################
void initLayoutPhoneLink() {
	icon_phone_linked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	icon_phone_lost = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LOST);

	GRect LayerBox = layer_get_bounds(phoneDisplay);
	GSize Box = gdraw_command_image_get_bounds_size(icon_phone_linked);
	Origin = GPoint(Box.w/3,(LayerBox.size.h - Box.h)/2);

	icon_calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);
	icon_time_elapsed = gdraw_command_image_create_with_resource(RESOURCE_ID_TIME_ELAPSED);

	isPhoneConnected=false;
	lastValue = 0;
}
//#################################################################################
void drawPhoneLink(Layer *frame, GContext* context) {
	gdraw_command_image_draw(context, icon_phone_linked, Origin);
	if (!isPhoneConnected) gdraw_command_image_draw(context, icon_phone_lost, Origin);

	// Converting Value to text...
 char Text[] = "     ";
 snprintf(Text, sizeof(Text), "%d bpm", lastValue);	
 GFont Font =  fonts_get_system_font(TIME_FONT);
 GRect Bounds = layer_get_bounds(frame);
 GPoint Center = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	

// Calculating Text Frame Position/Size
 GSize Size =  graphics_text_layout_get_content_size(Text,Font,Bounds,GTextOverflowModeWordWrap,GTextAlignmentCenter);
 GRect Container = GRect( Center.x - Size.w * 0.5, Center.y - Size.h * 0.5, Size.w, Size.h);

 graphics_context_set_text_color(context, GColorBlack);
 graphics_draw_text(context,Text,Font,Container,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 

}




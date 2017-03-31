#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "HeartBeatView.h"
//#################################################################################
GDrawCommandImage *icon_heart_beat;

int storedValue;
static GPoint Origin;
//#################################################################################
void initLayoutHeartBeat(){
	icon_heart_beat = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART_BEAT);

	GRect LayerBox = layer_get_bounds(phoneDisplay);
	GSize Box = gdraw_command_image_get_bounds_size(icon_heart_beat);
	Origin = GPoint(Box.w/3,(LayerBox.size.h - Box.h)/2);

	storedValue = 0;
}
//#################################################################################
void updateHeartBeat(int32_t value) {
	storedValue = (int)value;
	layer_mark_dirty(heartDisplay);
}
//#################################################################################
void drawHeartMonitor(Layer *frame, GContext* context)
{
	gdraw_command_image_draw(context, icon_heart_beat, Origin);


// Converting Value to text...
 char Text[] = "       ";
 snprintf(Text, sizeof(Text), "%d bpm", storedValue);
// APP_LOG(APP_LOG_LEVEL_DEBUG, "showing text [%s] ", Text);

 GFont Font =  fonts_get_system_font(VALUE_FONT);
 GRect Bounds = layer_get_bounds(frame);
 GPoint Center = GPoint( Bounds.size.w / 2, Bounds.size.h /2);

// Calculating Text Frame Position/Size
 GSize Size =  graphics_text_layout_get_content_size(Text,Font,Bounds,GTextOverflowModeWordWrap,GTextAlignmentCenter);
 GRect Container = GRect( Center.x - Size.w * 0.5, Center.y - Size.h * 0.5, Size.w, Size.h);

 graphics_context_set_text_color(context, TextColor);
 graphics_draw_text(context,Text,Font,Container,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);

}




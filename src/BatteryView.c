#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "BatteryView.h"

void updateBattery(BatteryChargeState batteryInfos) {
	BatteryLevel = batteryInfos.charge_percent;
	layer_mark_dirty(batteryDisplay);
}

void drawBattery(Layer *frame, GContext* context) {
/*	// Calculating Text Frame Position/Size
	GRect Frame = GRect(Center.x - Radius, Center.y - Radius, 2 * Radius, 2 * Radius);
	GSize Size =  graphics_text_layout_get_content_size(Text,Font,Frame,GTextOverflowModeWordWrap,GTextAlignmentCenter);
	GRect Container = GRect( Center.x - Size.w * 0.5, Center.y - Size.h * 0.5 - FontOffset, Size.w, Size.h);

	// Drawing Background Circle Track
	graphics_context_set_stroke_color(context, Colors[2]); 
	graphics_context_set_stroke_width(context, Radius * 0.5); 
	graphics_draw_circle(GraphicContext, ScreenCenter, CenterRadius);		

	// Drawing Surounding circle...
	graphics_context_set_fill_color(context, Colors[1]); 
	graphics_fill_circle(context, Center, Radius);		
	graphics_context_set_stroke_width(context, 1); 
	graphics_context_set_stroke_color(context, Colors[2]); 
	graphics_draw_circle(context, Center, Radius);		

	// Wrtting inner Text
	graphics_context_set_text_color(context, TextColor);
	graphics_draw_text(context,Text,Font,Container,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 
*/
}

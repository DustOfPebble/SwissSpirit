#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "BatteryView.h"
//#################################################################################
int BatteryLevel;
int GaugeRadius;
GPoint FrameCenter;
GRect BatteryValueBox;
GColor GaugeBackground;
GColor GaugeLevel;
GFont BatteryFont;
//#################################################################################
void initLayoutBattery() {
	BatteryFont = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
	GRect Bounds = layer_get_bounds(batteryDisplay);
	GSize TextSize = graphics_text_layout_get_content_size(FULL,BatteryFont,Bounds,GTextOverflowModeWordWrap,GTextAlignmentCenter);

	GPoint TextOrigin = GPoint( (Bounds.size.w - TextSize.w)/2, (Bounds.size.h - TextSize.h)/2 );
	BatteryValueBox = GRect(TextOrigin.x,TextOrigin.y,TextSize.w, TextSize.h);
	
	GaugeRadius = (Bounds.size.w < Bounds.size.h) ? Bounds.size.w/2 : Bounds.size.h/2;
	GaugeRadius = GaugeRadius - BACK_WIDTH;
	FrameCenter = grect_center_point(&Bounds);
	
	GaugeBackground = GColorPastelYellow;
	GaugeLevel = GColorMalachite;
}
//#################################################################################
void updateBattery(BatteryChargeState batteryInfos) {
	BatteryLevel = batteryInfos.charge_percent;
	layer_mark_dirty(batteryDisplay);
}
//#################################################################################
void drawBattery(Layer *frame, GContext* context) {

	// Drawing Background Circle Track
	graphics_context_set_stroke_color(context, GaugeBackground); 
	graphics_context_set_stroke_width(context, BACK_WIDTH); 
	graphics_draw_circle(context, FrameCenter, GaugeRadius);		

	// Drawing Gauge value circle...
	graphics_context_set_stroke_width(context, LEVEL_WIDTH); 
	graphics_context_set_stroke_color(context, GaugeLevel); 
	graphics_draw_circle(context, FrameCenter, GaugeRadius);		

	// Writing inner Text
	char BatteryString[4] = FULL;
	snprintf(BatteryString, sizeof(BatteryString), "%d%%", BatteryLevel);
	graphics_context_set_text_color(context, TextColor);
	graphics_draw_text(context,BatteryString,BatteryFont,BatteryValueBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 

}
//#################################################################################

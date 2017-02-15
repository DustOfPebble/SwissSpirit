#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "BatteryView.h"

//#################################################################################
void initLayoutBattery() {
	GFont Font = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD)
	GSize TextSize = graphics_draw_text("100%",Font,GTextOverflowModeWordWrap,GTextAlignmentCenter);
	GPoint TextOrigin = GPoint((batteryDisplay.size.w - TextSize.w )/2, (batteryDisplay.size.h - TextSize.h )/2 );
	BatteryValueBox = GRect(TextOrigin.x,TextOrigin.y,TextSize.w, TextSize.h);
	
	GaugeRadius = batteryDisplay.size.w / 2;
	FrameCenter = grect_center_point(batteryDisplay);
}
//#################################################################################
void updateBattery(BatteryChargeState batteryInfos) {
	BatteryLevel = batteryInfos.charge_percent;
	layer_mark_dirty(batteryDisplay);
}
//#################################################################################
void drawBattery(Layer *frame, GContext* context) {

	// Drawing Background Circle Track
	graphics_context_set_stroke_color(context, GaugeLevel); 
	graphics_context_set_stroke_width(context, 3); 
	graphics_draw_circle(GraphicContext, ScreenCenter, GaugeRadius);		

	// Drawing Surounding circle...
	graphics_context_set_fill_color(context, Colors[1]); 
	graphics_fill_circle(context, Center, Radius);		
	graphics_context_set_stroke_width(context, 1); 
	graphics_context_set_stroke_color(context, GaugeLevel); 
	graphics_draw_circle(context, Center, Radius);		

	// Wrtting inner Text
	graphics_context_set_text_color(context, TextColor);
	graphics_draw_text(context,Text,Font,BatteryValueBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 

}
//#################################################################################

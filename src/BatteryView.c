#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "BatteryView.h"
//#################################################################################
int SelectedIndicator;
int MaxIndicator;
GDrawCommandSequence *IndicatorCollection;
GPoint DrawOffset;
//#################################################################################
void initLayoutBattery() {
	GRect Bounds = layer_get_bounds(batteryDisplay);
	IndicatorCollection = gdraw_command_sequence_create_with_resource(RESOURCE_ID_BATTERY_POWER);
	GSize BatteryBox = gdraw_command_sequence_get_bounds_size(IndicatorCollection);
	DrawOffset = GPoint((Bounds.size.w - BatteryBox.w)/2,(Bounds.size.h - BatteryBox.h)/2);
	MaxIndicator = gdraw_command_sequence_get_num_frames(IndicatorCollection);
}
//#################################################################################
void updateBattery(BatteryChargeState batteryInfos) {
	SelectedIndicator = batteryInfos.charge_percent / 10;
	if (SelectedIndicator > MaxIndicator)  SelectedIndicator = MaxIndicator;
	layer_mark_dirty(batteryDisplay);
}
//#################################################################################
void drawBattery(Layer *frame, GContext* context) {	  
   GDrawCommandFrame *Indicator = gdraw_command_sequence_get_frame_by_index(IndicatorCollection, SelectedIndicator);
   gdraw_command_frame_draw(context, IndicatorCollection, Indicator, DrawOffset); 
}
//#################################################################################

#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "BatteryView.h"
//#################################################################################
static int index;
static int maxIndex;
GDrawCommandSequence *BatteryLevels;
GDrawCommandImage *Battery;

static GPoint Origin;
//#################################################################################
void initLayoutBattery() {
	GRect Bounds = layer_get_bounds(batteryDisplay);
	Battery = gdraw_command_image_create_with_resource(RESOURCE_ID_BATTERY);
	GSize BatteryBox = gdraw_command_image_get_bounds_size(Battery);
	Origin = GPoint((Bounds.size.w - BatteryBox.w)/2,(Bounds.size.h - BatteryBox.h)/2);
	BatteryLevels = gdraw_command_sequence_create_with_resource(RESOURCE_ID_BATTERY_LEVELS);
	maxIndex = gdraw_command_sequence_get_num_frames(BatteryLevels);
}
//#################################################################################
void updateBattery(BatteryChargeState batteryInfos) {
	index = batteryInfos.charge_percent / 10;
	if (index > maxIndex)  index = maxIndex;
	layer_mark_dirty(batteryDisplay);
}
//#################################################################################
void drawBattery(Layer *frame, GContext* context) {
   GDrawCommandFrame *Level = gdraw_command_sequence_get_frame_by_index(BatteryLevels, index);
   gdraw_command_frame_draw(context, BatteryLevels, Level, Origin);
   gdraw_command_image_draw(context, Battery, Origin);
}
//#################################################################################

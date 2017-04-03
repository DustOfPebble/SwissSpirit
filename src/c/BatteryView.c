#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "BatteryView.h"
//#################################################################################
GDrawCommandSequence *BatteryLevels;
GDrawCommandImage *Battery;
static int FrameIndex;
static int NbFrames;

GPoint BatteryIconXY;
//#################################################################################
void initLayoutBattery() {
	GRect Bounds = layer_get_bounds(batteryDisplay);
	Battery = gdraw_command_image_create_with_resource(RESOURCE_ID_BATTERY);
	GSize BatteryBox = gdraw_command_image_get_bounds_size(Battery);
	BatteryIconXY = GPoint((Bounds.size.w - BatteryBox.w)/2,(Bounds.size.h - BatteryBox.h)/2);
	BatteryLevels = gdraw_command_sequence_create_with_resource(RESOURCE_ID_BATTERY_LEVELS);
	NbFrames = gdraw_command_sequence_get_num_frames(BatteryLevels);
}
//#################################################################################
void updateBattery(BatteryChargeState batteryInfos) {
	FrameIndex = batteryInfos.charge_percent / 10;
	if (FrameIndex > NbFrames)  FrameIndex = NbFrames;
	layer_mark_dirty(batteryDisplay);
}
//#################################################################################
void drawBattery(Layer *frame, GContext* context) {
   GDrawCommandFrame *Level = gdraw_command_sequence_get_frame_by_index(BatteryLevels, FrameIndex);
   gdraw_command_frame_draw(context, BatteryLevels, Level, BatteryIconXY);
   gdraw_command_image_draw(context, Battery, BatteryIconXY);
}
//#################################################################################

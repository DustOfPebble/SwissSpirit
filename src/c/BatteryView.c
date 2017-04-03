#include <pebble.h>
#include "BatteryView.h"
//#################################################################################
GDrawCommandSequence *BatteryLevels;
GDrawCommandImage *Battery;
static int FrameIndex;
static int NbFrames;

static GRect LayerBox;
static GRect IconBox;	

GPoint BatteryIconXY;
//#################################################################################
void initLayoutBattery() {
	// Persistent parameters
	LayerBox = layer_get_bounds(batteryDisplay);
	
	//Load and Place Battery
	Battery = gdraw_command_image_create_with_resource(RESOURCE_ID_BATTERY);
	IconBox = GRectFromSize(gdraw_command_image_get_bounds_size(Battery));
	inCenterHrz(LayerBox, &IconBox);
	inCenterVrt(LayerBox, &IconBox);

	//Load Battery levels
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
   gdraw_command_frame_draw(context, BatteryLevels, Level, IconBox.origin);
   gdraw_command_image_draw(context, Battery, IconBox.origin);
}
//#################################################################################

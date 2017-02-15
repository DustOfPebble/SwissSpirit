#include <pebble.h>
#include "Globals.h"
//#################################################################################
int BatteryLevel;
GRect BatteryValueBox;
GColor GaugeBackground = GColorPastelYellow;
GColor GaugeLevel = GColorMalachite;
//#################################################################################
void initLayoutBattery(); 
void updateBattery(BatteryChargeState batteryStatus);
void drawBattery(Layer *frame, GContext* context);

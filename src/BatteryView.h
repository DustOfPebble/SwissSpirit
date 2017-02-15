#include <pebble.h>
#include "Globals.h"
//#################################################################################
void initLayoutBattery(); 
void updateBattery(BatteryChargeState batteryStatus);
void drawBattery(Layer *frame, GContext* context);

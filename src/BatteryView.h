#include <pebble.h>
#include "Globals.h"
//#################################################################################
#define FULL "100%"
#define BACK_WIDTH 6
#define LEVEL_WIDTH 3
//#################################################################################
void initLayoutBattery(); 
void updateBattery(BatteryChargeState batteryStatus);
void drawBattery(Layer *frame, GContext* context);

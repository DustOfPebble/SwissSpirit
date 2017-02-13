#include <pebble.h>
#include "Globals.h"

int BatteryLevel;

void updateBattery(BatteryChargeState batteryStatus);
void drawBattery(Layer *frame, GContext* context);

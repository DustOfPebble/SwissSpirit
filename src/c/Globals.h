#pragma once
#include <pebble.h>

extern TextLayer *timeDisplay;
extern TextLayer *dateDisplay;
extern Layer *batteryDisplay;
extern Layer *phoneDisplay;
extern Layer *heartDisplay;
extern Layer *weatherDisplay;

extern GFont ValueFont;
extern GFont UnitFont;
extern GColor TextColor;
extern GColor BackgroundColor;

extern int SecondsSinceSensorUpdate;
extern int SecondsSinceConnectEvent;
extern bool isPhoneConnected;

#pragma once
#include <pebble.h>

extern GDrawCommandImage *icon_heart_beat;
extern GDrawCommandImage *icon_calls_missed;
extern GDrawCommandImage *icon_time_elapsed;
extern GDrawCommandImage *icon_phone_lost;
extern GDrawCommandImage *icon_phone_linked;

extern TextLayer *timeDisplay;
extern TextLayer *dateDisplay;
extern Layer *batteryDisplay;
extern Layer *sharedDisplay;

extern GFont Font;

extern GColor TextColor;
extern GColor BackgroundColor;

extern int BatteryLevel;

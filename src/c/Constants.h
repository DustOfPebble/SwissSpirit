#pragma once
#include <pebble.h>

#define TimeFrame GRect( 0, 0, 144, 46)
#define DateFrame GRect( 0, 47, 98, 46)
#define BatteryFrame GRect( 99, 47, 46, 46)
#define SharedFrame GRect( 0, 93, 144, 76)

#define TIME_FONT FONT_KEY_BITHAM_42_BOLD
#define DATE_FONT FONT_KEY_ROBOTO_CONDENSED_21
#define VALUE_FONT FONT_KEY_BITHAM_30_BLACK
#define UNIT_FONT FONT_KEY_GOTHIC_24_BOLD

#define UPDATE_CLOCK 10

typedef enum {
  SensorValue = 0,

} AppKeys;


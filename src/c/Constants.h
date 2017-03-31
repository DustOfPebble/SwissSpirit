#pragma once
#include <pebble.h>

#define TimeFrame GRect( 0, 0, 144, 46)
#define DateFrame GRect( 0, 47, 98, 46)
#define BatteryFrame GRect( 99, 47, 46, 46)
#define SharedFrame GRect( 0, 93, 144, 76)

#define TIME_FONT FONT_KEY_BITHAM_42_BOLD
#define DATE_FONT FONT_KEY_GOTHIC_24_BOLD
#define VALUE_FONT FONT_KEY_GOTHIC_28_BOLD

typedef enum {
  SensorValue = 0,

} AppKeys;


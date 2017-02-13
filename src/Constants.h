#pragma once
#include <pebble.h>

typedef enum {
  HeartBeatMeasure = 0,  
  
} AppKeys;


#define TimeFrame GRect( 0, 0, 144, 46) 
#define DateFrame GRect( 0, 47, 98, 46) 
#define BatteryFrame GRect( 99, 47, 46, 46) 
#define SharedFrame GRect( 0, 93, 144, 76) 


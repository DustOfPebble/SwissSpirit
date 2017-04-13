#include <pebble.h>
#include "Globals.h"
#include "utils.h"

void initLayoutWeather();
void updateWeather(int8_t Index);
void updateWeatherHistory();
void drawWeather(Layer *frame, GContext* context);

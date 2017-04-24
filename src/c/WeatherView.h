#include <pebble.h>
#include "Globals.h"
#include "utils.h"
#include "Sender.h"

void initLayoutWeather();
void updateWeatherHistory();
void updateWeather(uint8_t WeatherID, int8_t Temperature);
void drawWeather(Layer *frame, GContext* context);

#include "WeatherView.h"
//#################################################################################
#define Sunny 0
#define SunnyCloudy 1
#define Cloudy 2
#define Rainy 3
#define Stormy 4
#define SunnyRainy 5

#define WeatherChangeDelay 30

static GDrawCommandSequence *Weather;
static int FrameWeatherIndex;
static int NbFramesWeather;

static GRect WeatherBox;
static GRect LayerBox;
static time_t TimeStampsWeatherChanged;
//#################################################################################
void initLayoutWeather() {
	// Set persistent vars
	LayerBox = layer_get_bounds(weatherDisplay);

	// Load Weather icons resources
	Weather = gdraw_command_sequence_create_with_resource(RESOURCE_ID_WEATHER);
	WeatherBox = GRectFromSize(gdraw_command_sequence_get_bounds_size(Weather));
	NbFramesWeather = gdraw_command_sequence_get_num_frames(Weather);

	// Place Weather
	inCenterVrt(LayerBox , &WeatherBox);
	inCenterHrz(LayerBox, &WeatherBox);

	// Load default vars values...
	FrameWeatherIndex = 0;
	time(&TimeStampsWeatherChanged);
}
//#################################################################################
void updateWeather(int8_t Index){
		if (Index >= NbFramesWeather) return;
		if (Index == FrameWeatherIndex) return;
		FrameWeatherIndex = Index;
		layer_mark_dirty(weatherDisplay);
	}
//#################################################################################
void updateWeatherHistory(){
		if (elapsed(TimeStampsWeatherChanged) < WeatherChangeDelay) return;
		time(&TimeStampsWeatherChanged);
		FrameWeatherIndex++;
		if (FrameWeatherIndex >= NbFramesWeather) FrameWeatherIndex =0;
		layer_mark_dirty(weatherDisplay);
	}
//#################################################################################
void drawWeather(Layer *frame, GContext* context) {

	// Draw selected Weather
	GDrawCommandFrame *SelectedWeather = gdraw_command_sequence_get_frame_by_index(Weather, FrameWeatherIndex);
	gdraw_command_frame_draw(context, Weather, SelectedWeather, WeatherBox.origin);
}




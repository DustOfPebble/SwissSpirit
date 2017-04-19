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

static GDrawCommandImage *Thermometer;
static int8_t Temperature = 0;


static GRect WeatherBox;
static GRect LayerBox;
static GRect ThermometerBox;
static GRect TemperatureBox;

static time_t TimeStampsWeatherChanged;
//#################################################################################
void initLayoutWeather() {
	// Set persistent vars
	LayerBox = layer_get_bounds(weatherDisplay);
	int Margin = LayerBox.size.w / 20;

	// Load thermometer icon resources
	Thermometer = gdraw_command_image_create_with_resource(RESOURCE_ID_THERMO);
	ThermometerBox = GRectFromSize(gdraw_command_image_get_bounds_size(Thermometer));

	// Load Weather icons resources
	Weather = gdraw_command_sequence_create_with_resource(RESOURCE_ID_WEATHER);
	WeatherBox = GRectFromSize(gdraw_command_sequence_get_bounds_size(Weather));
	NbFramesWeather = gdraw_command_sequence_get_num_frames(Weather);

	// Place Weather
	atCenter(Vertical, LayerBox , &WeatherBox);
	align(Left, LayerBox, &WeatherBox);
	translate(Horizontal, Margin, &WeatherBox);

	// place Thermometer
	align(Top, WeatherBox , &ThermometerBox);
	GRect FreeSpace;
	remainsAt(Right, LayerBox, WeatherBox, &FreeSpace);
	atCenter(Horizontal, FreeSpace, &ThermometerBox);

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

		Temperature++;
		if (Temperature > 50) Temperature = -30;
//		APP_LOG(APP_LOG_LEVEL_DEBUG, "Simulated Temp. :%d °C",Temperature);

		layer_mark_dirty(weatherDisplay);
	}
//#################################################################################
void drawWeather(Layer *frame, GContext* context) {
	// set Text color
	graphics_context_set_text_color(context, TextColor);

	// Draw selected Weather
	GDrawCommandFrame *SelectedWeather = gdraw_command_sequence_get_frame_by_index(Weather, FrameWeatherIndex);
	gdraw_command_frame_draw(context, Weather, SelectedWeather, WeatherBox.origin);

	// Show Thermometer
	gdraw_command_image_draw(context, Thermometer,  ThermometerBox.origin);

	// Calculate and Place String to display
	static char Text[] = "-99°";
	snprintf(Text, sizeof(Text), "%d°", Temperature);

	// Loading and place Temperature Text
	TemperatureBox = GRectFromText(Text,UnitFont,LayerBox);
	atCenter(Horizontal, ThermometerBox,  &TemperatureBox);
	align(Bottom, WeatherBox, &TemperatureBox);

	// Show Temperature value
	graphics_draw_text(context,Text,UnitFont,TemperatureBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);

}




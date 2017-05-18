#include "WeatherView.h"
//#################################################################################
#define NoWeather 0
#define Sunny 1
#define SunnyCloudy 2
#define Cloudy 3
#define Rainy 4
#define Stormy 5
#define SunnyRainy 6
#define Snowy 7
#define Foggy 8

#define WeatherUpdateDelay 22*60 // in seconds
#define InvalidTemperature -99

#define NbTemps 2
static int TempsSteps[NbTemps] = { 5, 18 };


static GDrawCommandSequence *Weather;
static GDrawCommandSequence *ThermometerRange;
static int FrameWeatherIndex;
static int NbFramesWeather;

static GDrawCommandImage *Thermometer;
static int8_t StoredTemperature;
static int FrameTemperatureIndex;

static GRect WeatherBox;
static GRect LayerBox;
static GRect ThermometerBox;
static GRect TemperatureBox;

static time_t TimeStampsWeatherUpdated;
//#################################################################################
void initLayoutWeather() {
	// Set persistent vars
	LayerBox = layer_get_bounds(weatherDisplay);
	int Margin = LayerBox.size.w / 20;

	// Load thermometer icon resources
	Thermometer = gdraw_command_image_create_with_resource(RESOURCE_ID_THERMO);
	ThermometerRange = gdraw_command_sequence_create_with_resource(RESOURCE_ID_THERMO_RANGE);
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
	StoredTemperature = InvalidTemperature;
	FrameTemperatureIndex = 2;
	TimeStampsWeatherUpdated = 0;
}
//#################################################################################
void updateWeatherHistory(){

	//	if (elapsed(TimeStampsWeatherUpdated) < WeatherUpdateDelay) return;
	//	send();
}
//#################################################################################
void updateWeather(uint8_t WeatherID, int8_t Temperature){
		bool NoChange = true;

		//vibes_double_pulse();

		if (WeatherID != FrameWeatherIndex) NoChange = false;
		if (Temperature != StoredTemperature) NoChange = false;
		if (NoChange) return;

		time(&TimeStampsWeatherUpdated);
		FrameWeatherIndex = WeatherID;
		StoredTemperature = Temperature;
		/*FrameTemperatureIndex = 3;
		if (StoredTemperature < 18) FrameTemperatureIndex = 2;
		if (StoredTemperature < 5) FrameTemperatureIndex = 1; */
		FrameTemperatureIndex = indexOf(TempsSteps, NbTemps, StoredTemperature) + 1;

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
	GDrawCommandFrame *SelectedRange = gdraw_command_sequence_get_frame_by_index(ThermometerRange, FrameTemperatureIndex);
	GDrawCommandFrame *Background = gdraw_command_sequence_get_frame_by_index(ThermometerRange, 0);
	gdraw_command_frame_draw(context, ThermometerRange, Background, ThermometerBox.origin);
	if (StoredTemperature != InvalidTemperature) gdraw_command_frame_draw(context, ThermometerRange, SelectedRange, ThermometerBox.origin);
	gdraw_command_image_draw(context, Thermometer,  ThermometerBox.origin);

	// Calculate and Place String to display
	static char Text[] = "-??";
	snprintf(Text, sizeof(Text), "%d", StoredTemperature);
	if (StoredTemperature == InvalidTemperature) snprintf(Text, sizeof(Text), "--");; // Invalid temprature

	// Loading and place Temperature Text
	TemperatureBox = GRectFromText(Text,ValueFont,LayerBox);
	atCenter(Horizontal, ThermometerBox,  &TemperatureBox);
	align(Bottom, WeatherBox, &TemperatureBox);

	// Show Temperature value
	graphics_draw_text(context,Text,ValueFont,TemperatureBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
}



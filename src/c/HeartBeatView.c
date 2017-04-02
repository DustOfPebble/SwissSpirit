#include "HeartBeatView.h"
//#################################################################################
GDrawCommandImage *icon_heart_beat;
static GPoint Origin;
GRect LayerBox;
GSize IconBox;

GFont ValueFont;
GRect ValueContainer;

GFont UnitFont;
GRect UnitContainer; 
char Unit[] = "b/m";

static int32_t displayedValue;
time_t TimeStampsUpdate;
//#################################################################################
void initLayoutHeartBeat(){
	icon_heart_beat = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART_BEAT);

	ValueFont = fonts_get_system_font(VALUE_FONT);
	UnitFont = fonts_get_system_font(UNIT_FONT);

	LayerBox = layer_get_bounds(phoneDisplay);
	IconBox = gdraw_command_image_get_bounds_size(icon_heart_beat);
	Origin = GPoint(LayerBox.size.w/10,(LayerBox.size.h - IconBox.h)/2);

	GSize TextSize =  graphics_text_layout_get_content_size(Unit,UnitFont,LayerBox,GTextOverflowModeWordWrap,GTextAlignmentCenter);
	int x_offset = (Origin.x + IconBox.w) + ((LayerBox.size.w - (Origin.x + IconBox.w)) - (TextSize.w)) / 2; 
	int y_offset = (Origin.y + IconBox.h)  - TextSize.h; 
	UnitContainer = GRect( x_offset, y_offset, TextSize.w, TextSize.h);

	displayedValue = 0;
	TimeStampsUpdate = 0;
}
//#################################################################################
void updateHeartBeatHistory() {
	SecondsSinceSensorUpdate = elapsed(TimeStampsUpdate);
}
//#################################################################################
void updateHeartBeat(int32_t value) {
	time(&TimeStampsUpdate);
	updateHeartBeatHistory(); // Update elapsed time for ViewSelector

	// Do we need to refresh the view ?
	if (displayedValue == value) return; 
	displayedValue = value;
	layer_mark_dirty(heartDisplay);   
}
//#################################################################################
void drawHeartBeat(Layer *frame, GContext* context)
{
	graphics_context_set_text_color(context, TextColor);

	char Value[] = "000";
	snprintf(Value, sizeof(Value), "%d", (int)displayedValue);

	GSize TextSize =  graphics_text_layout_get_content_size(Value,ValueFont,LayerBox,GTextOverflowModeWordWrap,GTextAlignmentCenter);
	int x_offset = (Origin.x + IconBox.w) + ((LayerBox.size.w - (Origin.x + IconBox.w)) - (TextSize.w)) / 2; 
	int y_offset = Origin.y; 
	ValueContainer = GRect( x_offset, y_offset, TextSize.w, TextSize.h);
	
	gdraw_command_image_draw(context, icon_heart_beat, Origin);
	graphics_draw_text(context,Value,ValueFont,ValueContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	graphics_draw_text(context,Unit,UnitFont,UnitContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
}




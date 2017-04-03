#include "HeartBeatView.h"
//#################################################################################
GDrawCommandImage *Heart;
static GPoint HeartIconXY;
GRect LayerBox;

static GFont ValueFont;
static GRect ValueContainer;

static GFont UnitFont;
static GRect UnitContainer;
static char Unit[] = "b/m";

static int32_t displayedValue;
time_t TimeStampsUpdate;
//#################################################################################
void initLayoutHeartBeat(){
	Heart = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART);

	ValueFont = fonts_get_system_font(VALUE_FONT);
	UnitFont = fonts_get_system_font(UNIT_FONT);

	LayerBox = layer_get_bounds(phoneDisplay);
	IconBox = GRectFromSize(gdraw_command_image_get_bounds_size(Heart));

	inCenterVrt(LayerBox, &IconBox);
	alignLeft(LayerBox,&IconBox);

	int Margin = LayerBox.size.w / 10;
	translate( GSize(Margin,0), &IconBox);

	HeartIconXY = IconBox.origin;

	UnitContainer = GRectFromText(Unit,UnitFont,LayerBox);
	GRect VBox = GRectFromPoint(GPoint(LayerBox.size.w, LayerBox.size.h));
	inBetweenHrz(IconBox, VBox, &UnitContainer);
	alignTop(IconBox, &UnitContainer);

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
	static char Value[] = "000";
	snprintf(Value, sizeof(Value), "%d", (int)displayedValue);

	GSize TextSize =  graphics_text_layout_get_content_size(Value,ValueFont,LayerBox,GTextOverflowModeWordWrap,GTextAlignmentCenter);
	int x_offset = (HeartIconXY.x + IconBox.w) + ((LayerBox.size.w - (HeartIconXY.x + IconBox.w)) - (TextSize.w)) / 2;
	int y_offset = HeartIconXY.y;
	ValueContainer = GRect( x_offset, y_offset, TextSize.w, TextSize.h);

	gdraw_command_image_draw(context, Heart, HeartIconXY);

	graphics_context_set_text_color(context, TextColor);
	graphics_draw_text(context,Value,ValueFont,ValueContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	graphics_draw_text(context,Unit,UnitFont,UnitContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
}




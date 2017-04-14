#include "HeartBeatView.h"
//#################################################################################
static GDrawCommandImage *Heart;
static GRect LayerBox;
static GRect IconBox;

static GRect ValueContainer;
static GRect UnitContainer;
static char Unit[] = "b/m";

static uint8_t displayedValue;
static time_t TimeStampsUpdate;
//#################################################################################
void initLayoutHeartBeat(){
	// Graphic persistent parameters
	LayerBox = layer_get_bounds(phoneDisplay);
	int Margin = LayerBox.size.w / 10;

	// Loading and place Heart icon
	Heart = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART);
	IconBox = GRectFromSize(gdraw_command_image_get_bounds_size(Heart));
	inCenterVrt(LayerBox, &IconBox);
	alignLeft(LayerBox,&IconBox);
	translate( GSize(Margin,0), &IconBox);

	// Loading and place Unit Text
	UnitContainer = GRectFromText(Unit,UnitFont,LayerBox);
	GRect FreeSpaceBox = GRectFromInner(LayerBox, IconBox);
	inCenterHrz(FreeSpaceBox, &UnitContainer);
	alignBottom(IconBox, &UnitContainer);

	// Init static Vars
	displayedValue = 0;
	TimeStampsUpdate = 0;
}
//#################################################################################
void updateHeartBeatHistory() {
	SecondsSinceSensorUpdate = elapsed(TimeStampsUpdate);
}
//#################################################################################
void updateHeartBeat(uint8_t value) {
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

	// Loading and place Value Text
	ValueContainer = GRectFromText(Value,ValueFont,LayerBox);
	GRect FreeSpaceBox = GRectFromInner(LayerBox, IconBox);
	inCenterHrz(FreeSpaceBox, &ValueContainer);
	alignTop(IconBox, &ValueContainer);

	gdraw_command_image_draw(context, Heart, IconBox.origin);

	graphics_context_set_text_color(context, TextColor);
	graphics_draw_text(context,Value,ValueFont,ValueContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	graphics_draw_text(context,Unit,UnitFont,UnitContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
}




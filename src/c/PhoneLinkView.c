#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

#include "PhoneLinkView.h"

//#################################################################################
GDrawCommandImage *Phone;
GDrawCommandImage *isLinked;
GDrawCommandImage *isNotLinked;

GDrawCommandImage *calls_missed;

GDrawCommandImage *Chrono;
GDrawCommandSequence *ChronoElapsed;
static int FrameIndex;
static int NbFrames;
#define MaxSteps 5
int ChronoSteps[MaxSteps] = { 8, 15, 24, 38, 60 };
int UnconnectedMinutesDisplayed = -1;

GPoint PhoneIconXY;
GPoint ChronoIconXY;

time_t TimeStampsLastConnected;
time_t TimeStampsStartConnected;
//#################################################################################
void initLayoutPhoneLink() {
	// Load Phone icons resources
	Phone = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE);
	isLinked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	isNotLinked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_NOT_LINKED);

	// Load Chrono icons resources & vars
	Chrono = gdraw_command_image_create_with_resource(RESOURCE_ID_CHRONO);
	ChronoElapsed = gdraw_command_sequence_create_with_resource(RESOURCE_ID_CHRONO_ELAPSED);
	NbFrames = gdraw_command_sequence_get_num_frames(ChronoElapsed);

	GSize Box;
	GRect LayerBox = layer_get_bounds(phoneDisplay);

	// Place the Phone icon
	Box = gdraw_command_image_get_bounds_size(Phone);
	PhoneIconXY = GPoint(LayerBox.size.w * 0.1,(LayerBox.size.h - Box.h)/2);

	// Place the Chrono icon
	Box = gdraw_command_image_get_bounds_size(Chrono);
	ChronoIconXY = GPoint((LayerBox.size.w * 0.9) - Box.w,(LayerBox.size.h - Box.h)/2);

	// Useless at this time
	calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);

	// Initialize vars
	time(&TimeStampsLastConnected);
	time(&TimeStampsStartConnected);
	FrameIndex = MaxSteps - 1;
}
//#################################################################################
void updatePhoneLinkHistory() {
	if (isPhoneConnected) time(&TimeStampsLastConnected);
	SecondsSinceConnection = elapsed(TimeStampsStartConnected);

	// Do we need to refresh the Display ? (Called also by TimeView)
	SecondsSinceDisconnection = elapsed(TimeStampsLastConnected);
	int UnconnectedMinutes = SecondsSinceDisconnection / 60;

	int MatchingIndex = MaxSteps - 1;
	for (int i = MaxSteps-1; i >=0 ; i --)
		if (UnconnectedMinutes < ChronoSteps[i] ) MatchingIndex = i;
	if (FrameIndex != MatchingIndex) {
		layer_mark_dirty(phoneDisplay); //Icon is different --> redraw required
		FrameIndex = MatchingIndex;
	}

	if (UnconnectedMinutesDisplayed != UnconnectedMinutes ) {
		layer_mark_dirty(phoneDisplay); //Value is different --> redraw required
		UnconnectedMinutesDisplayed = UnconnectedMinutes;
	}
}
//#################################################################################
void updatePhoneLink(bool connectedState) {
	// If switching from connected --> disconnect the save the time..
	if (!isPhoneConnected && connectedState) time(&TimeStampsStartConnected);

	// Notify user about state change by vibration ...
	if (connectedState) vibes_short_pulse();
	else vibes_long_pulse();

	// Store new state
	isPhoneConnected = connectedState;

	// Update connection history
	updatePhoneLinkHistory();

	// Call to this is triggered by a state change --> We force  a redraw ...
	layer_mark_dirty(phoneDisplay);
}
//#################################################################################
void drawPhoneLink(Layer *frame, GContext* context) {
	gdraw_command_image_draw(context, Phone, PhoneIconXY);
	if (isPhoneConnected)
	{
		gdraw_command_image_draw(context, isLinked, PhoneIconXY);
	}
	else
	{
/*		// Calculate/Place String to display
		static char Value[] = "000";
		snprintf(Value, sizeof(Value), "%d", (int)displayedValue);

		GSize TextSize =  graphics_text_layout_get_content_size(Value,ValueFont,LayerBox,GTextOverflowModeWordWrap,GTextAlignmentCenter);
		int x_offset = (HeartIconXY.x + IconBox.w) + ((LayerBox.size.w - (HeartIconXY.x + IconBox.w)) - (TextSize.w)) / 2;
		int y_offset = HeartIconXY.y;
		ValueContainer = GRect( x_offset, y_offset, TextSize.w, TextSize.h);
*/
		gdraw_command_image_draw(context, isNotLinked, PhoneIconXY);
		GDrawCommandFrame *Elapsed = gdraw_command_sequence_get_frame_by_index(ChronoElapsed, FrameIndex);
		gdraw_command_frame_draw(context, ChronoElapsed, Elapsed, ChronoIconXY);
		gdraw_command_image_draw(context, Chrono, ChronoIconXY);
	}
}




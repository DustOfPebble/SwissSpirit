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
#define MaxSteps 7
int ChronoSteps[MaxSteps] = { 5, 8, 15, 24, 38, 45, 60 };
int UnconnectedMinutesDisplayed = -1;

GRect IconPhone;
GRect IconChrono;
static GRect LayerBox;

static GRect ValueContainer;
static GRect UnitContainer;
static char Unit[] = "min";

time_t TimeStampsLastConnected;
time_t TimeStampsStartConnected;
//#################################################################################
void initLayoutPhoneLink() {
	// Set persistent vars
	LayerBox = layer_get_bounds(phoneDisplay);
	int Margin = LayerBox.size.w / 10;	

	// Load Phone icons resources
	Phone = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE);
	isLinked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	isNotLinked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_NOT_LINKED);
	
	// Place Phone Icon
	IconPhone = GRectFromSize(gdraw_command_image_get_bounds_size(Phone));
	inCenterVrt(LayerBox , &IconPhone);
	alignLeft(LayerBox, &IconPhone);
	translate(GSize(Margin,0), &IconPhone);

	// Load Chrono icons resources & vars
	Chrono = gdraw_command_image_create_with_resource(RESOURCE_ID_CHRONO);
	ChronoElapsed = gdraw_command_sequence_create_with_resource(RESOURCE_ID_CHRONO_ELAPSED);
	NbFrames = gdraw_command_sequence_get_num_frames(ChronoElapsed);

	// Place the Chrono icon
	IconChrono = GRectFromSize(gdraw_command_image_get_bounds_size(Chrono));
	inCenterVrt(LayerBox, &IconChrono);
	alignRight(LayerBox, &IconChrono);
	translate(GSize(-Margin,0), &IconChrono);
	
	// Loading and place Unit Text
	UnitContainer = GRectFromText(Unit,UnitFont,LayerBox);
	inBetweenHrz(IconPhone, IconChrono, &UnitContainer);
	alignBottom(IconPhone, &UnitContainer);
	
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
	int UnconnectedMinutes = SecondsSinceDisconnection / 1;
		
	// Select matching index
	int MatchingIndex = MaxSteps - 1;
	for (int i = MaxSteps-1; i >=0 ; i--)
		if (UnconnectedMinutes < ChronoSteps[i] ) MatchingIndex = i;
		
	if (FrameIndex != MatchingIndex) {
		FrameIndex = MatchingIndex;
		layer_mark_dirty(phoneDisplay); //Icon is different --> redraw required
	}

	if (UnconnectedMinutesDisplayed != UnconnectedMinutes ) {
		UnconnectedMinutesDisplayed = UnconnectedMinutes;
		layer_mark_dirty(phoneDisplay); //Value is different --> redraw required
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
	// Show Phone without status
	gdraw_command_image_draw(context, Phone,  IconPhone.origin);
	
	if (isPhoneConnected)
	{
		gdraw_command_image_draw(context, isLinked, IconPhone.origin);
	}
	else
	{
		// Calculate and Place String to display
		static char Value[] = "00";
		if (UnconnectedMinutesDisplayed < 60) snprintf(Value, sizeof(Value), "%d", UnconnectedMinutesDisplayed);
		else snprintf(Value, sizeof(Value), "--");

		// Loading and place Value Text
		ValueContainer = GRectFromText(Value,ValueFont,LayerBox);
		inBetweenHrz(IconPhone, IconChrono, &ValueContainer);
		alignTop(IconPhone, &ValueContainer);


		// Draw Chrono icon and elapsed
		gdraw_command_image_draw(context, isNotLinked, IconPhone.origin);
		GDrawCommandFrame *Elapsed = gdraw_command_sequence_get_frame_by_index(ChronoElapsed, FrameIndex);
		gdraw_command_frame_draw(context, ChronoElapsed, Elapsed, IconChrono.origin);
		gdraw_command_image_draw(context, Chrono, IconChrono.origin);
		
		// Draw text and unit values
		graphics_context_set_text_color(context, TextColor);
		graphics_draw_text(context,Value,ValueFont,ValueContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
		graphics_draw_text(context,Unit,UnitFont,UnitContainer,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	}
}




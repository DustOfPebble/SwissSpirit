#include "PhoneLinkView.h"
//#################################################################################
static GDrawCommandImage *Phone;
static GDrawCommandSequence *PhoneLink;
#define isLinked 0
#define isNotLinked 1

static GDrawCommandImage *CallsMissed;
static GDrawCommandImage *MessagesMissed;

static GDrawCommandImage *Chrono;
static GDrawCommandSequence *ChronoElapsed;
static int FrameIndex;

#define MaxSteps 7
static int ChronoSteps[MaxSteps] = { 5, 8, 15, 24, 38, 45, 60 };
static int UnconnectedMinutesDisplayed = -1;

static uint8_t MissedCallsCounter = 0;
static uint8_t MissedMessagesCounter = 0;

static GRect PhoneBox;
static GRect ChronoBox;
static GRect CallsBox;
static GRect MessagesBox;
static GRect LayerBox;

static GRect CallsCountBox;
static GRect MessagesCountBox;
static GRect ValueBox;
static GRect UnitBox;
static char Unit[] = "min";

static time_t TimeStampsLastConnected;
static time_t TimeStampsStartConnected;
//#################################################################################
void initLayoutPhoneLink() {
	// Set persistent vars
	LayerBox = layer_get_bounds(phoneDisplay);
	int Margin = LayerBox.size.w / 10;

	// Load Phone icons resources
	Phone = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE);
	PhoneLink = gdraw_command_sequence_create_with_resource(RESOURCE_ID_PHONE_LINK);

	// Place Phone Icon
	PhoneBox = GRectFromSize(gdraw_command_image_get_bounds_size(Phone));
	atCenter(Vertical,LayerBox , &PhoneBox);
	align(Left, LayerBox, &PhoneBox);
	translate(Horizontal, Margin, &PhoneBox);

	// Load Chrono icons resources & vars
	Chrono = gdraw_command_image_create_with_resource(RESOURCE_ID_CHRONO);
	ChronoElapsed = gdraw_command_sequence_create_with_resource(RESOURCE_ID_CHRONO_ELAPSED);

	// Place the Chrono icon
	ChronoBox = GRectFromSize(gdraw_command_image_get_bounds_size(Chrono));
	atCenter(Vertical, LayerBox, &ChronoBox);
	align(Right, LayerBox, &ChronoBox);
	translate(Horizontal, -Margin, &ChronoBox);

	// Loading and place Unit Text
	UnitBox = GRectFromText(Unit,UnitFont,LayerBox);
	inMiddle(Horizontal, PhoneBox, ChronoBox, &UnitBox);
	align(Bottom, PhoneBox, &UnitBox);

	// Load icons for calls and Messages
	CallsMissed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS);
	MessagesMissed = gdraw_command_image_create_with_resource(RESOURCE_ID_MESSAGES);

	// Place Messages icon (at End)
	MessagesBox = GRectFromSize(gdraw_command_image_get_bounds_size(MessagesMissed));
	align(Top, PhoneBox, &MessagesBox);
	align(Right, LayerBox, &MessagesBox);
	translate(Horizontal, -Margin, &MessagesBox);

	// Place Calls icon (in the Middle)
	CallsBox = GRectFromSize(gdraw_command_image_get_bounds_size(CallsMissed));
	align(Top, PhoneBox , &CallsBox);
	inMiddle(Horizontal, PhoneBox, MessagesBox, &CallsBox);

	// Initialize vars
	time(&TimeStampsLastConnected);
	time(&TimeStampsStartConnected);
	FrameIndex = MaxSteps - 1;
}
//#################################################################################
void updatePhoneEvents(uint8_t Calls, uint8_t Messages){
	bool isChanged = false;
	if (Calls != MissedCallsCounter) isChanged = true;
	if (Messages != MissedMessagesCounter) isChanged = true;
	if (!isChanged) return;
	MissedCallsCounter = Calls;
	MissedMessagesCounter = Messages;
	layer_mark_dirty(phoneDisplay);
}
//#################################################################################
void updatePhoneLinkHistory() {
	if (isPhoneConnected) time(&TimeStampsLastConnected);
	SecondsSinceConnection = elapsed(TimeStampsStartConnected);

	// Do we need to refresh the Display ? (Called also by TimeView)
	SecondsSinceDisconnection = elapsed(TimeStampsLastConnected) + 1; // +1 force display
	int UnconnectedMinutes = SecondsSinceDisconnection / 60;

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
	// If switching from connected --> disconnect ==> save the time..
	if (!isPhoneConnected && connectedState) time(&TimeStampsStartConnected);
	// Store new state
	isPhoneConnected = connectedState;

	// Notify user about state change by vibration ...
	if (isPhoneConnected) vibes_short_pulse();
	else vibes_long_pulse();

	// Update connection history
	updatePhoneLinkHistory();

	// Call to this is triggered by a state change --> We force a view selection ...
	updateViewSelector();
}
//#################################################################################
void drawPhoneLink(Layer *frame, GContext* context) {
	// set Text color
	graphics_context_set_text_color(context, TextColor);

	// Show Phone without status
	gdraw_command_image_draw(context, Phone,  PhoneBox.origin);
	GDrawCommandFrame *linkState;

	if (isPhoneConnected)
	{
		// Place Messages missed value
		static char MessagesCount[] = "00";
		snprintf(MessagesCount, sizeof(MessagesCount), "%d", (int)MissedMessagesCounter);
		MessagesCountBox = GRectFromText(MessagesCount,ValueFont,LayerBox);
		atCenter(Horizontal, MessagesBox, &MessagesCountBox);
		align(Bottom, PhoneBox, &MessagesCountBox);

		// Place Calls missed value
		static char CallsCount[] = "00";
		snprintf(CallsCount, sizeof(CallsCount), "%d", (int)MissedCallsCounter);
		CallsCountBox = GRectFromText(CallsCount,ValueFont,LayerBox);
		atCenter(Horizontal, CallsBox, &CallsCountBox);
		align(Bottom, PhoneBox, &CallsCountBox);

		// Draw icons ...
		linkState = gdraw_command_sequence_get_frame_by_index(PhoneLink, isLinked);
		gdraw_command_frame_draw(context, PhoneLink, linkState, PhoneBox.origin);
		gdraw_command_image_draw(context, CallsMissed, CallsBox.origin);
		gdraw_command_image_draw(context, MessagesMissed, MessagesBox.origin);

		// Draw texts ...
		graphics_draw_text(context,CallsCount,ValueFont,CallsCountBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
		graphics_draw_text(context,MessagesCount,ValueFont,MessagesCountBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	}
	else
	{
		// Calculate and Place String to display
		static char Value[] = "00";
		if (UnconnectedMinutesDisplayed < 60) snprintf(Value, sizeof(Value), "%d", UnconnectedMinutesDisplayed);
		else snprintf(Value, sizeof(Value), "--");

		// Loading and place Value Text
		ValueBox = GRectFromText(Value,ValueFont,LayerBox);
		inMiddle(Horizontal, PhoneBox, ChronoBox, &ValueBox);
		align(Top, PhoneBox, &ValueBox);

		// Draw Chrono icon and elapsed
		linkState = gdraw_command_sequence_get_frame_by_index(PhoneLink, isNotLinked);
		gdraw_command_frame_draw(context, PhoneLink, linkState, PhoneBox.origin);
		GDrawCommandFrame *Elapsed = gdraw_command_sequence_get_frame_by_index(ChronoElapsed, FrameIndex);
		gdraw_command_frame_draw(context, ChronoElapsed, Elapsed, ChronoBox.origin);
		gdraw_command_image_draw(context, Chrono, ChronoBox.origin);

		// Draw text and unit values
		graphics_draw_text(context,Value,ValueFont,ValueBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
		graphics_draw_text(context,Unit,UnitFont,UnitBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	}
}




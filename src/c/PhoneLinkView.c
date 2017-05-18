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

#define NbChrono 13
static int ChronoSteps[NbChrono] = { 3, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60 };

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

static time_t TimeStampsConnectEvent;
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
	GRect FreeSpace;
	remainsAt(Right,LayerBox,PhoneBox, &FreeSpace);
	atCenter(Horizontal, FreeSpace, &ChronoBox);

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
	FrameIndex = -1;
	TimeStampsConnectEvent=0;
	time(&TimeStampsConnectEvent);
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

	// Updates timer for view selector
	SecondsSinceConnectEvent = elapsed(TimeStampsConnectEvent);
	int UnconnectedMinutes = SecondsSinceConnectEvent / 60;

	// Select/Check changed View for Chrono
	/*int MatchingIndex = MaxSteps - 1;
	for (int i = MaxSteps-1; i >= 1 ; i--)
		if (UnconnectedMinutes < ChronoSteps[i] ) MatchingIndex = i; */
	int MatchingIndex = indexOf(ChronoSteps,NbChrono,UnconnectedMinutes) + 1;

	if (FrameIndex != MatchingIndex) {
		FrameIndex = MatchingIndex;
		layer_mark_dirty(phoneDisplay); //Icon is different --> redraw required
	}

	// Check if displayed value have changed
	if (UnconnectedMinutesDisplayed != UnconnectedMinutes ) {
		UnconnectedMinutesDisplayed = UnconnectedMinutes;
		layer_mark_dirty(phoneDisplay); //Value is different --> redraw required
	}
}
//#################################################################################
void updatePhoneLink(bool connectState) {
	// Store new state
	isPhoneConnected = connectState;

	// Notify user about state change by vibration ...
	if (isPhoneConnected) vibes_short_pulse();
	else vibes_long_pulse();

	// save TimeStamps
	time(&TimeStampsConnectEvent);

	// Update connection history
	updatePhoneLinkHistory();

	// Call to this is triggered by a state change --> We force a view arbitration ...
	updateViewSelector();
	layer_mark_dirty(phoneDisplay); //Value is different --> redraw required
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
		// Draw phone link icon
		linkState = gdraw_command_sequence_get_frame_by_index(PhoneLink, isNotLinked);
		gdraw_command_frame_draw(context, PhoneLink, linkState, PhoneBox.origin);


		// Draw Elapsed and Chrono
		GDrawCommandFrame *Background = gdraw_command_sequence_get_frame_by_index(ChronoElapsed, 0);
		GDrawCommandFrame *Elapsed = gdraw_command_sequence_get_frame_by_index(ChronoElapsed, FrameIndex);
		gdraw_command_frame_draw(context, ChronoElapsed, Background, ChronoBox.origin);
		gdraw_command_frame_draw(context, ChronoElapsed, Elapsed, ChronoBox.origin);
		gdraw_command_image_draw(context, Chrono, ChronoBox.origin);


		// Calculate and Place String to display
		static char Value[] = "00";
		if (UnconnectedMinutesDisplayed < 60) snprintf(Value, sizeof(Value), "%d", UnconnectedMinutesDisplayed);
		else snprintf(Value, sizeof(Value), "--");

		// Loading and place Value Text
		ValueBox = GRectFromText(Value,ValueFont,LayerBox);
		atCenter(Horizontal | Vertical, ChronoBox, &ValueBox);

		// Draw text and unit values
		graphics_draw_text(context,Value,ValueFont,ValueBox,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
	}
}




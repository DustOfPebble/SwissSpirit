#include <pebble.h>
#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

void updatePhoneLink(bool connected);
void updatePhoneLinkHistory();
void updatePhoneEvents(int8_t Calls, int8_t Messages);
void initLayoutPhoneLink();
void drawPhoneLink(Layer *frame, GContext* context);

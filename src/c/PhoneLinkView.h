#include <pebble.h>
#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

void updatePhoneLink(bool connectState);
void updatePhoneLinkHistory();
void updatePhoneEvents(uint8_t Calls, uint8_t Messages);
void initLayoutPhoneLink();
void drawPhoneLink(Layer *frame, GContext* context);

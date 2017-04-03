#include <pebble.h>
#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

void updatePhoneLink(bool connected);
void updatePhoneLinkHistory();
void updateDemo(int32_t value);
void initLayoutPhoneLink();
void drawPhoneLink(Layer *frame, GContext* context);

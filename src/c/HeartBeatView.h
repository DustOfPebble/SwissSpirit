#include <pebble.h>
#include "Globals.h"
#include "Constants.h"
#include "utils.h"
#include "ViewSelector.h"

void initLayoutHeartBeat();
void updateHeartBeat(int32_t value);
void updateHeartBeatHistory();
void drawHeartBeat(Layer *frame, GContext* context);


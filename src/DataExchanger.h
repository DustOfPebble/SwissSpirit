#include <pebble.h>

#include "Constants.h"
#include "PhoneLinkView.h"

void received(DictionaryIterator *PhoneDatas, void *context);
void dropped(AppMessageResult reason, void *context);
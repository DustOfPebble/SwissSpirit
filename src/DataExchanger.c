#include "DataExchanger.h"
//#################################################################################
void received(DictionaryIterator *PhoneDatas, void *context) {
// Does this message contain a given value?
	Tuple *isHeartRate = dict_find(PhoneDatas, HeartBeatMeasure);
	if(isHeartRate)	{ updateDemo(isHeartRate->value->int32);}
}

void dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped. Reason: %d", (int)reason);
  updateDemo(254);
}
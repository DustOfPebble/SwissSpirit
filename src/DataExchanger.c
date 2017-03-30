#include "DataExchanger.h"
//#################################################################################
void incomming_datas(DictionaryIterator *PhoneDatas, void *context) {
// Does this message contain a given value?
	Tuple *isHeartRate = dict_find(PhoneDatas, HeartBeatMeasure);
	if(isHeartRate)	{ updateDemo(isHeartRate->value->int32);}
}

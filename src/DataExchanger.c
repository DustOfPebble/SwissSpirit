#include "DataExchanger.h"
//#################################################################################
void manage_phone_incomming_datas(DictionaryIterator *PhoneDatas, void *context) {
// Does this message contain a given value?
	Tuple *isHeartRate = dict_find(PhoneDatas, HeartBeatMeasure);
	if(isHeartRate)	{	}
}

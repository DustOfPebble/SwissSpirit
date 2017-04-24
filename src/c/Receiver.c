#include "Receiver.h"

//#################################################################################
void received_done(DictionaryIterator *PhoneDatas, void *context) {
/**********************************
 *  Local vars to monitor changes *
 * ********************************/
	uint8_t NewCalls,NewMessages;
	bool isPhoneChanged = false;

	uint8_t NewBeat;
	bool isSensorChanged = false;

	uint8_t NewWeatherID;
	int8_t NewTemperature;
	bool isWeatherChanged = false;
/**********************************
 *    Parse Dictionnary values    *
 * ********************************/
    Tuple *Item = dict_read_first(PhoneDatas);
	while (Item)
	{
//		APP_LOG(APP_LOG_LEVEL_DEBUG, "Found key[%d] with playload of %d bytes",(int) item->key, (int)item->length);
		// Phone events management
		if (Item->key == CallsCount) {
			NewCalls = Item->value->uint8;
			isPhoneChanged = true;
		}
		if (Item->key == MessagesCount) {
			NewMessages = Item->value->uint8;
			isPhoneChanged = true;
		}

		// Beat sensor management
		if (Item->key == SensorBeat) {
			NewBeat = Item->value->uint8;
			isSensorChanged = true;
		}
		// Weather informations management
		if (Item->key == WeatherSkyNow) {
			NewWeatherID = Item->value->uint8;
			isWeatherChanged = true;
		}
		if (Item->key == WeatherTemperatureNow) {
			NewTemperature = Item->value->int8;
			isWeatherChanged = true;
		}


		// Cycle informations management

		// Trip informations management


		// Loop over next Item
		Item = dict_read_next(PhoneDatas);
	}
/**********************************
 *           Update HMI           *
 * ********************************/
	if (isPhoneChanged) updatePhoneEvents(NewCalls, NewMessages);
	if (isSensorChanged) updateHeartBeat(NewBeat);
	if (isWeatherChanged) updateWeather(NewWeatherID,NewTemperature);
}

void received_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped [Error %d]", (int)reason);
}

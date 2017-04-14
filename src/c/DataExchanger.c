#include "DataExchanger.h"

//#################################################################################
void received_done(DictionaryIterator *PhoneDatas, void *context) {
/**********************************
 *  Local vars to monitor changes *
 * ********************************/
	uint8_t NewCalls,NewMessages;
	bool isPhoneChanged = false;

	uint8_t NewBeat;
	bool isSensorChanged = false;
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
}

void received_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped [Error %d]", (int)reason);
}

void sent_done(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message sent !");
}

void sent_failed(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message not sent [Error %d]", (int)reason);
}

void send(int Value) {
/*
  DictionaryIterator *iter;
  AppMessageResult Status;

  Status = app_message_outbox_begin(&iter);
  if(Status != APP_MSG_OK) { APP_LOG(APP_LOG_LEVEL_ERROR, "Prepare failed [Error:%d]", (int)Status); return;}

  dict_write_int(iter, SensorValue, &Value, sizeof(int), true);
  Status = app_message_outbox_send();
  if(Status != APP_MSG_OK) { APP_LOG(APP_LOG_LEVEL_ERROR, "Send failed [Error:%d]", (int)Status); return;}
*/
}



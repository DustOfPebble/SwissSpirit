#include "DataExchanger.h"

//#################################################################################
void received_done(DictionaryIterator *PhoneDatas, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message received !");
  Tuple *contains = dict_find(PhoneDatas, SensorValue);
  if(contains) {
	  APP_LOG(APP_LOG_LEVEL_DEBUG, "searched key:SensorValue[%d] has value %ds",(int) SensorValue, (int)contains->value->int32);
	  updateDemo(contains->value->int32);
  }

/*
    Tuple *item = dict_read_first(PhoneDatas);
	while (item)
	{
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Found key[%d] with playload of %d bytes",(int) item->key, (int)item->length);
		item = dict_read_next(PhoneDatas);
	}
*/
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
  DictionaryIterator *iter;
  AppMessageResult Status;

  Status = app_message_outbox_begin(&iter);
  if(Status != APP_MSG_OK) { APP_LOG(APP_LOG_LEVEL_ERROR, "Prepare failed [Error:%d]", (int)Status); return;}

  dict_write_int(iter, SensorValue, &Value, sizeof(int), true);
  Status = app_message_outbox_send();
  if(Status != APP_MSG_OK) { APP_LOG(APP_LOG_LEVEL_ERROR, "Send failed [Error:%d]", (int)Status); return;}
}



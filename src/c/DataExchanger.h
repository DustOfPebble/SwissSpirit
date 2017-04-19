#include <pebble.h>

#include "Constants.h"
#include "utils.h"
#include "HeartBeatView.h"
#include "PhoneLinkView.h"
#include "WeatherView.h"
#include "ViewSelector.h"
#include "keys.h"

//**************************************************************
void received_done(DictionaryIterator *PhoneDatas, void *context);
void received_dropped(AppMessageResult reason, void *context);
void sent_done(DictionaryIterator *iter, void *context) ;
void sent_failed(DictionaryIterator *failed, AppMessageResult reason, void *context) ;
void send(int Value) ;

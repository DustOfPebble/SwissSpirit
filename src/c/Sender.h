#include <pebble.h>
#include "Constants.h"
#include "keys.h"

//**************************************************************
void sent_done(DictionaryIterator *iter, void *context) ;
void sent_failed(DictionaryIterator *failed, AppMessageResult reason, void *context) ;
void send() ;

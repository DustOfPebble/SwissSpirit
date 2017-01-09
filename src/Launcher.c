#include <pebble.h>

#include "Globals.h"

#include "Constants.h"
#include "HeartView.h"
// Milliseconds between frames

#define DELTA 100

Window *window = NULL;
Layer *layer = NULL;
GPath *heartObject = NULL;
GDrawCommandSequence *heartVector = NULL;

//#################################################################################
static void trigRedraw(void *context)
{
// Draw the next frame
layer_mark_dirty(layer); 
}
//#################################################################################
static void inbox_received_callback(DictionaryIterator *scanDictionnary, void *context)
{
// Does this message contain a temperature value?
Tuple *isHeartRate = dict_find(scanDictionnary, HeartRateUpdate);
if(isHeartRate)
{
// Start a beat sequence
app_timer_register(DELTA, trigRedraw, NULL);
}
}
//#################################################################################
void loading(Window *window)
{
Layer *rootLayer = window_get_root_layer(window);
layer = layer_create(layer_get_frame(rootLayer));
layer_add_child(rootLayer, layer);	
layer_set_update_proc(layer, redraw);

heartVector = gdraw_command_sequence_create_with_resource(RESOURCE_ID_HEARTBEAT);

// Continue the sequence
app_timer_register(DELTA, trigRedraw, NULL);
}
//#################################################################################
void unLoading(Window *window)
{
gdraw_command_sequence_destroy(heartVector);
layer_destroy(layer);
}
//#################################################################################
int main(void)
{
// Loading and Applying settings
window = window_create();
window_set_background_color(window, GColorWhite);
window_set_window_handlers(window, (WindowHandlers) { .load = loading, .unload = unLoading });
window_stack_push(window, true);

// Register to be notified about inbox received events
app_message_register_inbox_received(inbox_received_callback);


// Entering event loop until exit requested
app_event_loop();

// Exiting --> Clearing Memory
window_destroy(window);
}

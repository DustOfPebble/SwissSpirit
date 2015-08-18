#include <pebble.h>

#include "RingsView.h"

Window *NeedleWindow;
Layer *GraphicArea;

void UpdateTimeView(struct tm* TimeInfos, TimeUnits Unit)
{
  // Copying Hours and Minutes before asking for a redraw ..
  Secondes = TimeInfos->tm_sec;
  Minutes = TimeInfos->tm_min;
  Hours = TimeInfos->tm_hour;
  
  // Marking NeedleWindow as to be redrawn ...
  layer_mark_dirty(GraphicArea);
}
//#################################################################################
void Loading(Window *window)
{
  Layer *RootLayer = window_get_root_layer(window);
  GraphicArea = layer_create(layer_get_frame(RootLayer));
  layer_add_child(RootLayer, GraphicArea);	
  layer_set_update_proc(GraphicArea, drawRings);
}

//#################################################################################
void UnLoading(Window *window)
{
  tick_timer_service_unsubscribe();
  layer_destroy(GraphicArea);
}

//#################################################################################
int main(void)
{
// Loading and Applying settings
  NeedleWindow = window_create();
  window_set_background_color(NeedleWindow, GColorMelon);
  window_set_window_handlers(NeedleWindow, (WindowHandlers) { .load = Loading, .unload = UnLoading });
  window_stack_push(NeedleWindow, true);
  tick_timer_service_subscribe(SECOND_UNIT, UpdateTimeView); // Forcing a redraw every second ...
  
// Entering event loop until exit requested
  app_event_loop();
  
// Exiting --> Clearing Memory
   window_destroy(NeedleWindow);
}

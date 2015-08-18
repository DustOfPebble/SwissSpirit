#include <pebble.h>

#include "RingsView.h"

static Window *NeedleWindow;
static Layer *GraphicArea;

void UpdateTimeView(struct tm* TimeInfos, TimeUnits Unit)
{
  // Copying Hours and Minutes before asking for a redraw ..
  Minutes = TimeInfos->tm_min;
  Hours = TimeInfos->tm_hour;
  
  // Marking NeedleWindow as to be redrawn ...
//  layer_mark_dirty(GraphicArea);
  APP_LOG(APP_LOG_LEVEL_INFO, "Updating Time View");
}
//#################################################################################
void Loading(Window *window)
{
  GraphicArea = window_get_root_layer(window);
 // layer_set_update_proc(GraphicArea, drawRings);
}

//#################################################################################
void UnLoading(Window *window)
{
  tick_timer_service_unsubscribe();
}

//#################################################################################
int main(void)
{
// Loading and Applying settings
  NeedleWindow = window_create();
  window_set_background_color(NeedleWindow, GColorRichBrilliantLavender);
  window_set_window_handlers(NeedleWindow, (WindowHandlers) { .load = Loading, .unload = UnLoading });
  window_stack_push(NeedleWindow, true);
//  Update_Time_View(current_time, MINUTE_UNIT);
  tick_timer_service_subscribe(SECOND_UNIT, UpdateTimeView); // Forcing a redraw every second ...
  
// Entering event loop until exit requested
  app_event_loop();
  
// Exiting --> Clearing Memory
   window_destroy(NeedleWindow);
}

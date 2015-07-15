#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_battery_layer;
static TextLayer *s_connection_layer;

static void handle_battery(BatteryChargeState charge_state)
{
  static char battery_text[] = "100% charged";

  if (charge_state.is_charging) snprintf(battery_text, sizeof(battery_text), "charging");
  else snprintf(battery_text, sizeof(battery_text), "%d%% charged", charge_state.charge_percent);
  
  text_layer_set_text(s_battery_layer, battery_text);
}

static void Update_Time_View(struct tm* tick_time, TimeUnits units_changed)
{
  // Needs to be static because it's used by the system later.
  static char s_time_text[] = "00:00";

  strftime(s_time_text, sizeof(s_time_text), "%H:%M", tick_time);
  text_layer_set_text(s_time_layer, s_time_text);

  handle_battery(battery_state_service_peek());
}

static void handle_bluetooth(bool connected)
{
  text_layer_set_text(s_connection_layer, connected ? "Connected" : "Disconnected");
}

static void main_window_load(Window *window)
{
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_time_layer = text_layer_create(GRect(0, 25, bounds.size.w, 54));
  text_layer_set_text_color(s_time_layer, GColorIndigo);
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  s_connection_layer = text_layer_create(GRect(0, 90, bounds.size.w, 34));
  text_layer_set_text_color(s_connection_layer, GColorBlueMoon);
  text_layer_set_background_color(s_connection_layer, GColorClear);
  text_layer_set_font(s_connection_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(s_connection_layer, GTextAlignmentCenter);
  handle_bluetooth(bluetooth_connection_service_peek());

  s_battery_layer = text_layer_create(GRect(0, 120, bounds.size.w, 34));
  text_layer_set_text_color(s_battery_layer, GColorJazzberryJam);
  text_layer_set_background_color(s_battery_layer, GColorClear);
  text_layer_set_font(s_battery_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentCenter);
  text_layer_set_text(s_battery_layer, "100% charged");

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  Update_Time_View(current_time, MINUTE_UNIT);

  tick_timer_service_subscribe(MINUTE_UNIT, Update_Time_View);
  battery_state_service_subscribe(handle_battery);
  bluetooth_connection_service_subscribe(handle_bluetooth);

  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_connection_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_battery_layer));
}

static void main_window_unload(Window *window)
{
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_connection_layer);
  text_layer_destroy(s_battery_layer);
}

static void init()
{
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorRichBrilliantLavender);
  window_set_window_handlers(s_main_window, (WindowHandlers) { .load = main_window_load, .unload = main_window_unload });
  window_stack_push(s_main_window, true);
}

static void deinit()
{
  window_destroy(s_main_window);
}

int main(void)
{
  init();
  app_event_loop();
  vibes_double_pulse();
  deinit();
}

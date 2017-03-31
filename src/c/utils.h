#include <pebble.h>

// Returning a time structure on the curent time
tm* get_time();

// Returning Elapsed seconds between now and provided time;
int elapsed_seconds(tm* reference);

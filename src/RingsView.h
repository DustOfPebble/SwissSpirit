#include <pebble.h>

// Called Function for rendering screen
void DrawRings(Layer *SelectedLayer, GContext* GraphicContext);

// Called Function for rendering One ring ...
void DrawRing(Layer *SelectedLayer, GContext* GraphicContex, int Value, uint16_t Radius,  GPoint Center );

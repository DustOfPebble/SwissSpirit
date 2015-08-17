#include <pebble.h>

// Called Function for rendering Background
void DrawRings(Layer *SelectedLayer, GContext* GraphicContext)
{
// Getting and adapting screen geometry
  GRect Bounds = layer_get_bounds(SelectedLayer);
  uint16_t MinutesRadius = Bounds.size.w / 3;
  uint16_t HoursRadius = Bounds.size.w / 4;
  GPoint Center = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	
  
  // Setting graphic properties
 graphics_context_set_stroke_color(GraphicContext, GColorWindsorTan); 
graphics_context_set_stroke_width(GraphicContext, 3);
	
 // Drawing Hours Ring ...	
 DrawRing(SelectedLayer, GraphicContext, Hours, HoursRadius, Center)
// Drawing Minutes Ring ...	
 DrawRing(SelectedLayer, GraphicContext, Minutes, MinutesRadius, Center)
}

// Called Function for rendering One ring ...
void DrawRing(Layer *SelectedLayer, GContext* GraphicContex, int Value, uint16_t Radius, GPoint Center)
{
// Converting Value to text...
 char Text[] = "00";
 snprintf(Text, sizeof(Text), "%d", Value);	
 
 // Calculating Position of Ring from Value and Radius...
 u
 graphics_draw_circle(GraphicContext, Center, Radius);		



}
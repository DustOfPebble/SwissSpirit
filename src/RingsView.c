#include <pebble.h>

// Called Function for rendering Background
void DrawRings(Layer *SelectedLayer, GContext* GraphicContext)
{
  GRect Bounds = layer_get_bounds(SelectedLayer);
  uint16_t Radius = Bounds.size.w / 3;
  uint8_t Width = Radius / 10;	
  GPoint Center = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	

  graphics_context_set_stroke_width(GraphicContext, Width);

  graphics_context_set_stroke_color(GraphicContext, GColorWindsorTan); 
  graphics_draw_circle(GraphicContext, Center, Radius);		

  graphics_context_set_stroke_color(GraphicContext, GColorVeryLightBlue);
  graphics_draw_circle(GraphicContext, Center, Radius+5);		

  graphics_context_set_stroke_color(GraphicContext, GColorIslamicGreen);
  graphics_draw_circle(GraphicContext, Center, Radius-5);		
}


#include <pebble.h>
#include "RingsView.h"

int Hours = 0;
int Minutes = 0;

// ################# Called Function for Calculating Ring Center  ################# 
GPoint getRingCenter(float Angle, uint16_t Radius, GPoint ScreenCenter)
{
   return (GPoint)
	{ 
	  .x = (int16_t)( sin_lookup(TRIG_MAX_ANGLE * Angle) * Radius ) + (int32_t) ScreenCenter.x ,
	  .y = (int16_t)( -cos_lookup(TRIG_MAX_ANGLE *Angle) * Radius ) - (int32_t) ScreenCenter.y
        };	
}

// ################# Called Function for rendering One ring  ################# 
void drawRing(Layer *SelectedLayer, GContext* GraphicContext, int Value, uint16_t Radius, GPoint Center)
{
// Converting Value to text...
 char Text[] = "00";
 snprintf(Text, sizeof(Text), "%d", Value);	

// Drawing Text 
 

// Writing Surounding circle...
 graphics_draw_circle(GraphicContext, Center, Radius);		

}

// ################# Called Function for rendering Background ################# 
void drawRings(Layer *SelectedLayer, GContext* GraphicContext)
{
 APP_LOG(APP_LOG_LEVEL_INFO, "Drawing Rings!");

// Getting and adapting screen geometry
  GRect Bounds = layer_get_bounds(SelectedLayer);
  uint16_t MinutesRadius = Bounds.size.w / 3;
  uint16_t HoursRadius = Bounds.size.w / 4;
  GPoint ScreenCenter = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	
  
// Setting graphic properties
  graphics_context_set_stroke_color(GraphicContext, GColorWindsorTan); 
  graphics_context_set_stroke_width(GraphicContext, 3);
	
  GPoint RingCenter;
// Drawing Hours Ring ...
  RingCenter = getRingCenter(Hours/12.0, HoursRadius, ScreenCenter);		
  drawRing(SelectedLayer, GraphicContext, Hours, 10, RingCenter);

// Drawing Minutes Ring ...	
  RingCenter = getRingCenter(Minutes/60.0, MinutesRadius, ScreenCenter);	
  drawRing(SelectedLayer, GraphicContext, Minutes, 10, RingCenter);
}




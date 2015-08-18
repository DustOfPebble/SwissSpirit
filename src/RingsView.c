#include <pebble.h>
#include "RingsView.h"

int Hours = 0;
int Minutes = 0;

// ################# Called Function for Calculating Ring Center  ################# 
GPoint getRingCenter(float Angle, uint16_t Radius, GPoint ScreenCenter)
{
  APP_LOG(APP_LOG_LEVEL_INFO, "Angle/Radius: [%d,%d]",(int)Angle, Radius);
  GPoint Point =  (GPoint)
	{ 
	  .x = ( sin_lookup(TRIG_MAX_ANGLE * Angle)  * Radius / TRIG_MAX_RATIO) +  ScreenCenter.x ,
	  .y = ( -cos_lookup(TRIG_MAX_ANGLE * Angle)  * Radius / TRIG_MAX_RATIO) +  ScreenCenter.y
        };	

 
  APP_LOG(APP_LOG_LEVEL_INFO, "Hours/Minutes: [%d,%d]",Hours, Minutes);
  APP_LOG(APP_LOG_LEVEL_INFO, "x/y: [%d,%d]",Point.x,Point.y);

  return Point;
}

// ################# Called Function for rendering One ring  ################# 
void drawRing(Layer *SelectedLayer, GContext* GraphicContext, int Value, uint16_t Radius, GPoint Center)
{
// Converting Value to text...
 char Text[] = "00";
 snprintf(Text, sizeof(Text), "%d", Value);	



// Drawing Text 
  APP_LOG(APP_LOG_LEVEL_INFO, "Center: [%d,%d]", Center.x, Center.y);
 GFont Font =  fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
 GRect Frame = GRect(Center.x - Radius, Center.y - Radius, 2 * Radius, 2 * Radius);
 graphics_draw_text(GraphicContext,Text,Font,Frame,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 

// Writing Surounding circle...
 graphics_draw_circle(GraphicContext, Center, Radius);		

}

// ################# Called Function for rendering Background ################# 
void drawRings(Layer *SelectedLayer, GContext* GraphicContext)
{
// Getting and adapting screen geometry
  GRect Bounds = layer_get_bounds(SelectedLayer);
  uint16_t MinutesRadius = Bounds.size.w / 3;
  uint16_t HoursRadius = Bounds.size.w / 4;
  GPoint ScreenCenter = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	
  
// Setting graphic properties
  graphics_context_set_stroke_color(GraphicContext, GColorWindsorTan); 
  graphics_context_set_stroke_width(GraphicContext, 3);
  graphics_context_set_text_color(GraphicContext, GColorBlack);
	
  GPoint RingCenter;
// Drawing Hours Ring ...
//  RingCenter = getRingCenter((float)Hours/12.0, 0, ScreenCenter);		
  RingCenter = getRingCenter((float)Hours / 12.0 , HoursRadius, ScreenCenter);		
  drawRing(SelectedLayer, GraphicContext, Hours, 10, RingCenter);

// Drawing Minutes Ring ...	
//  RingCenter = getRingCenter((float)Minutes/60.0, 0, ScreenCenter);	
  RingCenter = getRingCenter((float)Minutes / 60.0 , MinutesRadius, ScreenCenter);	
  drawRing(SelectedLayer, GraphicContext, Minutes, 10, RingCenter);

}




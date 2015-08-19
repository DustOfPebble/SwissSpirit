#include <pebble.h>
#include "RingsView.h"

int Hours = 0;
int Minutes = 0;
int Secondes = 0;

static GFont Font;
static  GRect Bounds;
static GPoint ScreenCenter;
static GSize MaxSize;
static int MaxDimension;
static int CircleRadius;

static int SecondesRadius;
static int MinutesRadius;
static int HoursRadius;

static int FontOffset;

static GColor HoursColors[3];
static GColor MinutesColors[3];
static GColor SecondesColors[3];

// ################# Called Function for Calculating Ring Center  ################# 
GPoint getRingCenter(float Angle, uint16_t Radius, GPoint ScreenCenter)
{
  GPoint Point =  (GPoint)
	{ 
	  .x = ( sin_lookup(TRIG_MAX_ANGLE * Angle)  * Radius / TRIG_MAX_RATIO) +  ScreenCenter.x ,
	  .y = ( -cos_lookup(TRIG_MAX_ANGLE * Angle)  * Radius / TRIG_MAX_RATIO) +  ScreenCenter.y
        };	

  return Point;
}

// ################# Called Function for rendering One ring  ################# 
void drawRing(Layer *SelectedLayer, GContext* GraphicContext, int Value, int Radius, int CenterRadius, GPoint Center, GColor Colors[])
{
// Converting Value to text...
 char Text[] = "00";
 snprintf(Text, sizeof(Text), "%d", Value);	

// Calculating Text Frame Position/Size
 GRect Frame = GRect(Center.x - Radius, Center.y - Radius, 2 * Radius, 2 * Radius);
 GSize Size =  graphics_text_layout_get_content_size(Text,Font,Frame,GTextOverflowModeWordWrap,GTextAlignmentCenter);
 GRect Container = GRect( Center.x - Size.w * 0.5, Center.y - Size.h * 0.5 - FontOffset, Size.w, Size.h);

// Drawing Background Circle Track
 graphics_context_set_stroke_color(GraphicContext, Colors[2]); 
 graphics_context_set_stroke_width(GraphicContext, Radius * 0.5); 
 graphics_draw_circle(GraphicContext, ScreenCenter, CenterRadius);		

// Drawing Surounding circle...
 graphics_context_set_fill_color(GraphicContext, Colors[1]); 
 graphics_fill_circle(GraphicContext, Center, Radius);		
 graphics_context_set_stroke_width(GraphicContext, 1); 
 graphics_context_set_stroke_color(GraphicContext, Colors[2]); 
 graphics_draw_circle(GraphicContext, Center, Radius);		

// Wrtting inner Text
 graphics_context_set_text_color(GraphicContext, Colors[0]);
 graphics_draw_text(GraphicContext,Text,Font,Container,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 

}

// ################# Called Function for rendering Background ################# 
void drawRings(Layer *SelectedLayer, GContext* GraphicContext)
{
// Getting and adapting to screen geometry on first call
  Font =  fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  Bounds = layer_get_bounds(SelectedLayer);
  ScreenCenter = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	
  MaxSize =  graphics_text_layout_get_content_size("00",Font,Bounds,GTextOverflowModeWordWrap,GTextAlignmentCenter);
  FontOffset = MaxSize.h * 0.20;	

  MaxDimension = ( MaxSize.w > MaxSize.h) ? MaxSize.w : MaxSize.h;  	
  CircleRadius = MaxDimension * 0.5;	

  SecondesRadius = (Bounds.size.w * 0.5) - CircleRadius;
  SecondesColors[0] = GColorDarkGreen;
  SecondesColors[1] = GColorMintGreen;
  SecondesColors[2] = GColorMalachite;

  MinutesRadius = (Bounds.size.w * 0.5) - (3 * CircleRadius);
  MinutesColors[0] = GColorDukeBlue;
  MinutesColors[1] = GColorElectricBlue;
  MinutesColors[2] = GColorPictonBlue;

  HoursRadius = (Bounds.size.w * 0.5) - (5 * CircleRadius);
  HoursColors[0] = GColorJazzberryJam;
  HoursColors[1] = GColorRichBrilliantLavender;
  HoursColors[2] = GColorPurpureus;

  graphics_context_set_antialiased(GraphicContext, true);

  GPoint RingCenter;
// Drawing Hours Ring ...
  RingCenter = getRingCenter((float)Hours / 12.0 , HoursRadius, ScreenCenter);		
  drawRing(SelectedLayer, GraphicContext, Hours, CircleRadius, HoursRadius, RingCenter, HoursColors);

// Drawing Minutes Ring ...	
  RingCenter = getRingCenter((float)Minutes / 60.0 , MinutesRadius, ScreenCenter);	
  drawRing(SelectedLayer, GraphicContext, Minutes, CircleRadius, MinutesRadius, RingCenter ,MinutesColors);

// Drawing Secondes Ring ...
  RingCenter = getRingCenter((float)Secondes / 60.0 , SecondesRadius, ScreenCenter);		
  drawRing(SelectedLayer, GraphicContext, Secondes, CircleRadius, SecondesRadius, RingCenter, SecondesColors);

}




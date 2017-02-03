#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "SharedViews.h"


// ################# Called Function for rendering Background ################# 
void drawTime(Layer *surface, GContext* context){
	// Converting Value to text...
	char HoursText[] = "00";
	snprintf(Text, sizeof(Text), "%d", Hours);		
	char MinutesText[] = "00";
	snprintf(Text, sizeof(Text), "%d", Minutes);		

// Getting and adapting to screen geometry on first call
	Font =  fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
	Bounds = layer_get_bounds(SelectedLayer);
	ScreenCenter = GPoint( Bounds.size.w / 2, Bounds.size.h /2);	
	MaxSize =  graphics_text_layout_get_content_size("00",Font,Bounds,GTextOverflowModeWordWrap,GTextAlignmentCenter);
	FontOffset = MaxSize.h * 0.20;	
	
// Writting Time string
	graphics_context_set_text_color(GraphicContext, Colors[0]);
	graphics_draw_text(GraphicContext,Text,Font,Container,GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL); 

}

void drawDate(Layer *surface, GContext* context){

}


void drawBattery(Layer *surface, GContext* context) {
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

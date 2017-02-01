#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "SharedViews.h"


// ################# Called Function for rendering Background ################# 
void drawTime(Layer *surface, GContext* context){
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(heartVector, framesIndex);

  // If another frame was found, draw it
  if (frame) { gdraw_command_frame_draw(context, heartVector, frame, GPoint(0, 0)); }

  // Advance to the next frame, wrapping if neccessary
  int framesMax = gdraw_command_sequence_get_num_frames(heartVector);
  framesIndex++;
  if (framesIndex == framesMax) { framesIndex = 0;}

}

void drawDate(Layer *surface, GContext* context){

}


void drawBattery(Layer *surface, GContext* context){

}

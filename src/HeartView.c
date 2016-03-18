#include <pebble.h>

#include "Globals.h"
#include "Constants.h"
#include "HeartView.h"

static int framesIndex = 0;

// ################# Called Function for rendering Background ################# 
void redraw(Layer *surface, GContext* context)
{
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(heartVector, framesIndex);

  // If another frame was found, draw it
  if (frame) { gdraw_command_frame_draw(context, heartVector, frame, GPoint(0, 0)); }

  // Advance to the next frame, wrapping if neccessary
  int framesMax = gdraw_command_sequence_get_num_frames(heartVector);
  framesIndex++;
  if (framesIndex == framesMax) { framesIndex = 0;}

}




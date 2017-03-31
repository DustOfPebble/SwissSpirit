#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "HeartBeatView.h"
//#################################################################################
GDrawCommandImage *icon_heart_beat;
//#################################################################################
void initLayoutHeartBeat(){
	icon_heart_beat = gdraw_command_image_create_with_resource(RESOURCE_ID_HEART_BEAT);
}
//#################################################################################
void drawHeartMonitor(Layer *frame, GContext* context)
{
/* GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(heartVector, framesIndex);

  // If another frame was found, draw it
  if (frame) { gdraw_command_frame_draw(context, heartVector, frame, GPoint(0, 0)); }

  // Advance to the next frame, wrapping if neccessary
  int framesMax = gdraw_command_sequence_get_num_frames(heartVector);
  framesIndex++;
  if (framesIndex == framesMax) { framesIndex = 0;}
*/
}




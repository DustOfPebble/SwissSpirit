#include <pebble.h>

#include "Globals.h"
#include "Constants.h"

#include "PhoneLinkView.h"
//#################################################################################
GDrawCommandImage *icon_phone_linked;
GDrawCommandImage *icon_phone_lost;

GDrawCommandImage *icon_calls_missed;
GDrawCommandImage *icon_time_elapsed;
//#################################################################################
void initLayoutPhoneLink() {
	icon_phone_linked = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LINKED);
	icon_phone_lost = gdraw_command_image_create_with_resource(RESOURCE_ID_PHONE_LOST);
	
	icon_calls_missed = gdraw_command_image_create_with_resource(RESOURCE_ID_CALLS_MISSED);
	icon_time_elapsed = gdraw_command_image_create_with_resource(RESOURCE_ID_TIME_ELAPSED);
}
//#################################################################################
void drawPhoneLink(Layer *frame, GContext* context)
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




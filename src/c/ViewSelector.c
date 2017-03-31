#include "ViewSelector.h"

void updateViewSelector(){

	/* Business logic :
	 * - Phone disconnection leads heart sensor --> Disconnection screen overides
	 * - Phone reconnection --> schow screen connection for 30 secondes --> then allows HeartBeatDisplay.
	 * - Sensor lost --> wait 30 seconds until showing back phoneDisplay
	 */

APP_LOG(APP_LOG_LEVEL_DEBUG, "Connected since:%d s Disconnected since:%d s SensorUpdate sinc %d s.",SecondsSinceConnection, SecondsSinceDisconnection, SecondsSinceSensorUpdate);

	if (SecondsSinceDisconnection > 0)	{
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(phoneDisplay,false);
		return;
	}

	if (SecondsSinceSensorUpdate > 30) {
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(phoneDisplay,false);
		return;
	}

	if ((SecondsSinceConnection > 30) || (SecondsSinceSensorUpdate < 2)) {
		layer_set_hidden(heartDisplay,false);
		layer_set_hidden(phoneDisplay,true);
		return;
	}
}

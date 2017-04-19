#include "ViewSelector.h"

void updateViewSelector(){

	/* Business logic :
	 * - Default Display is Weather ==> Fallback
	 * - Phone disconnection leads heart sensor --> Disconnection screen overides
	 * - Phone reconnection --> schow screen connection for 30 secondes --> then allows other display.
	 * - Sensor lost criteria --> wait 30 seconds without update to consider sensor lost
	 */

	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Connected since:%d s Disconnected since:%d s SensorUpdate sinc %d s.",SecondsSinceConnection, SecondsSinceDisconnection, SecondsSinceSensorUpdate);

	// Disconnection --> Switch to Phone disconnected
	if (SecondsSinceDisconnection > 0)	{
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(weatherDisplay,true);
		layer_set_hidden(phoneDisplay,false);
		return;
	}
	// Sensor Lost --> Switch Weather Mode
	if (SecondsSinceSensorUpdate > 30) {
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(phoneDisplay,true);
		layer_set_hidden(weatherDisplay,false);
		return;
	}

	// Phone Connection --> Wait 15 seconds -> 2 options
	if (SecondsSinceConnection > 15) {
		// Sensor update < 5s --> Show sensors
		if  (SecondsSinceSensorUpdate < 5) {
			layer_set_hidden(weatherDisplay,true);
			layer_set_hidden(phoneDisplay,true);
			layer_set_hidden(heartDisplay,false);
			return;
		}
	}

	// None of previous case catch ==> Fallback mode
	layer_set_hidden(heartDisplay,true);
	layer_set_hidden(phoneDisplay,true);
	layer_set_hidden(weatherDisplay,false);
}

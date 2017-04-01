#include "ViewSelector.h"

void updateViewSelector(){

	/* Business logic :
	 * - Phone disconnection leads heart sensor --> Disconnection screen overides
	 * - Phone reconnection --> schow screen connection for 30 secondes --> then allows HeartBeatDisplay.
	 * - Sensor lost/recovery --> wait 30 seconds after phone reconnection until showing back sensorDisplay
	 */

	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Connected since:%d s Disconnected since:%d s SensorUpdate sinc %d s.",SecondsSinceConnection, SecondsSinceDisconnection, SecondsSinceSensorUpdate);

	// Disconnection --> Switch to Phone discconnected
	if (SecondsSinceDisconnection > 0)	{
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(phoneDisplay,false);
		return;
	}
	// Sensor Lost --> Switch to phone mode
	if (SecondsSinceSensorUpdate > 30) {
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(phoneDisplay,false);
		return;
	}

	// Wait 30 seconds of Phone connected history before displaying sensor
	if ((SecondsSinceConnection > 15) && (SecondsSinceSensorUpdate < 2)) {
		layer_set_hidden(heartDisplay,false);
		layer_set_hidden(phoneDisplay,true);
		return;
	}

	// None of previous case catch ==> Fallback mode = PhoneView
		layer_set_hidden(heartDisplay,true);
		layer_set_hidden(phoneDisplay,false);
}

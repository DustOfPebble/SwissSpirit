#include "ViewSelector.h"
//############################################################################
void showWeather() {
	layer_set_hidden(heartDisplay,true);
	layer_set_hidden(phoneDisplay,true);
	layer_set_hidden(weatherDisplay,false);
}
//############################################################################
void showPhoneLink() {
	layer_set_hidden(heartDisplay,true);
	layer_set_hidden(weatherDisplay,true);
	layer_set_hidden(phoneDisplay,false);
}
//############################################################################
void showHeartSensor() {
	layer_set_hidden(weatherDisplay,true);
	layer_set_hidden(phoneDisplay,true);
	layer_set_hidden(heartDisplay,false);
}
//############################################################################
void updateViewSelector(){

	/****************************************************************************************************
	 *  Business logic :
	 *  ================
	 * 0: Phone disconnected --> Highest priority until reconnection
	 * 1: Phone Connected --> Highest priority for 1 minute
	 * 1: Heart Sensor --> Sensor lost : Wait 1 minute => Lower priority screen
	 * 2: Weather --> No Weather update => Lower priority screen
	 * 3: Phone Connected --> [Calls/Messages]
	 *
	 * Nb: This is called every minute and Connect/Disconnect
	 ******************************************************************************************************/

	// Phone disconnection ==> Shows until reconnection
	if (!isPhoneConnected)	{
		showPhoneLink();
		return;
	}

	// Phone connected ==> Shows at least 30 seconds [30 --> 30+59]
	if (SecondsSinceConnectEvent < 30) {
		showPhoneLink();
		return;
	}

	// Heart Sensor ==> Shows at least 30 seconds after last update [30 --> 30+59]
	if (SecondsSinceSensorUpdate < 30) {
		showHeartSensor();
		return;
	}

	// Fallback mode
	showWeather();
}

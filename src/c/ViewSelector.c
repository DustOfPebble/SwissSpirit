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
	 * 0: Phone disconnected --> Highest Priority
	 * 1: Heart Sensor --> Sensor lost : Wait 30 secondes => Lower priority screen
	 * 2: Weather --> No Weather update => Lower priority screen
	 * 3: Phone Connected --> [Calls/Messages]
	 ******************************************************************************************************/

	// Disconnection ==> Higest priority
	if (!isPhoneConnected)	{
		showPhoneLink();
		return;
	}

	// Phone Connected ==> if connected since 15s
	if (SecondsSinceConnectEvent < 15) {
		showPhoneLink();
		return;
	}

	// Heart Sensor connected ==> High priority
	if (SecondsSinceSensorUpdate < 30) {
		showHeartSensor();
		return;
	}

	// Fallback mode
	showWeather();
}

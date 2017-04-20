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
	if (SecondsSinceDisconnection > 0)	{
		showPhoneLink();
		return;
	}

	// Heart Sensor connected ==> High priority
	if (SecondsSinceSensorUpdate < 30) {
		// Phone Connected ==>
		if (SecondsSinceConnection < 15) {
			showHeartSensor();
			return;
		}
		showWeather();
		return;
	}

	// Fallback mode
	showWeather();
}

#ifndef MqttManager_h
#define MqttManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxMQTT.h"
#include "Configuration.h"

class MqttManager
{
	public:
		//! Setup the MQTT Manager
		void setup(MQTT_Configuration _mqttConfig);

    void publish(message);

		//! Close the MQTT Manager
		void close();

	private:
		string message;
};

#endif /* CsvManager_h */

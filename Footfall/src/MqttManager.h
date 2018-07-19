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

    void publish(std::string message);

		//! Close the MQTT Manager
		void close();

	private:
    ofxMQTT MQTT;
		int _QoS;
		string _MQTTTopic;
		string _id;
		string _username;
		string _password;
};

#endif /* CsvManager_h */

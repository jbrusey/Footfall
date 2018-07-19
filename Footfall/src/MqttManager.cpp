#include "MqttManager.h"
#include <unistd.h>
//--------------------------------------------------------------
void MqttManager::setup(MQTT_Configuration _mqttConfig)
{
	cout << "Setting Up MQTT Manager" << endl;

	char hostname[HOST_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);

	_id = _mqttConfig.id;
	_username = _mqttConfig.username;
	_password = _mqttConfig.password;

	_QoS = _mqttConfig.QoS;
	_MQTTTopic = "Street/" + ofToString(hostname) + "/pedestrians";

  MQTT.begin(_mqttConfig.server, _mqttConfig.port);
	connect(3);
	MQTT.update();
}

void MqttManager::connect(int attempts)
{
	while (!MQTT.Connected || attempts != 0)
	{
		cout << "Connecting to MQTT..." << endl;
		MQTT.connect(_id, _username, _password);
		attempts--;
	}
}

void MqttManager::publish(std::string message)
{
	connect(3);
  MQTT.publish(_MQTTTopic, message, _QoS, false);
  MQTT.update();
}

void MqttManager::close()
{
}

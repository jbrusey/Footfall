#include "MqttManager.h"
#include <unistd.h>
//--------------------------------------------------------------
void MqttManager::setup(MQTT_Configuration _mqttConfig)
{
	cout << "Setting Up MQTT Manager";

  MQTT.begin(_mqttConfig.server, _mqttConfig.port);

  if (MQTT.connect(_mqttConfig.id, _mqttConfig.username, _mqttConfig.password))
    cout << "MQTT Connected!" << endl;
	else
    cout << "Couldn't connect to MQTT!" << endl;

	MQTT.update();

	char hostname[HOST_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);

  _QoS = _mqttConfig.QoS;
	_MQTTTopic = "Street/" + ofToString(hostname) + "/pedestrians";
}

void MqttManager::publish(std::string message)
{
  MQTT.update();
  MQTT.publish(_MQTTTopic, message, _QoS, false);
  MQTT.update();
}

void MqttManager::close()
{
}

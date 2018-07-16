#include "MqttManager.h"
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

  _QoS = _mqttConfig.QoS;
}

void MqttManager::publish(std::string message)
{
  MQTT.update();
  MQTT.publish("Street/1/pedestrians", message, _QoS, false);
  MQTT.update();
}

void MqttManager::close()
{
}

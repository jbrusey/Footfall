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

  _QoS = _mqttConfig.QoS;
  _Sequence = 0;
}

void MqttManager::publish(std::string message)
{
  MQTT.update();

  char hostname[HOST_NAME_MAX];
  gethostname(hostname, HOST_NAME_MAX);

  string sep = ",";
  string csv = ofToString(time(0)) + sep +
                   hostname + sep +
                   message + sep +
                   ofToString(_Sequence);

  MQTT.publish("Street/1/pedestrians", csv, _QoS, false);
  MQTT.update();

	_Sequence++;
}

void MqttManager::close()
{
}

// * Name: ConfigurationManager.cpp
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#include "ConfigurationManager.h"
//--------------------------------------------------------------
void ConfigurationManager::loadConfiguration(string file)
{
	cout << "Loading Configuration";
	if (!configFile.open(file))
	{
		cout << " - Could not find the Configuration File!" << endl;
		return;
	}
	else
	{
		cout << " - Configuration File Found!" << endl;

		// App Settings
		config.useMQTT = configFile["Footfall"]["AppConfig"]["usemqtt"].asBool();
		config.useCsvLogging = configFile["Footfall"]["AppConfig"]["usecsvlogging"].asBool();

		config.cameraConfig.useVideoRecording = configFile["Footfall"]["CameraConfig"]["usevideorecording"].asBool();
		config.cameraConfig.videoFileName = configFile["Footfall"]["CameraConfig"]["videofilename"].asString();
		config.cameraConfig.camerawidth = configFile["Footfall"]["CameraConfig"]["camerawidth"].asInt();
		config.cameraConfig.cameraheight = configFile["Footfall"]["CameraConfig"]["cameraheight"].asInt();
		config.cameraConfig.fps = configFile["Footfall"]["CameraConfig"]["fps"].asInt();

		config.cameraConfig.dilateAmount = configFile["Footfall"]["CameraConfig"]["dilate"].asInt();
		config.cameraConfig.erodeAmount = configFile["Footfall"]["CameraConfig"]["erode"].asInt();
		config.cameraConfig.blur = configFile["Footfall"]["CameraConfig"]["blur"].asInt();
		config.cameraConfig.threshold = configFile["Footfall"]["CameraConfig"]["threshold"].asInt();

		config.cameraConfig.mogThreshold = configFile["Footfall"]["CameraConfig"]["mogthreshold"].asInt();
		config.cameraConfig.history = configFile["Footfall"]["CameraConfig"]["history"].asInt();
		config.cameraConfig.bTrackShadows = configFile["Footfall"]["CameraConfig"]["trackshadows"].asInt();
		config.cameraConfig.shadowPixelRatio = configFile["Footfall"]["CameraConfig"]["shadowPixelRatio"].asFloat();

		config.cameraConfig.bFlipH = configFile["Footfall"]["CameraConfig"]["fliphorizontally"].asBool();
		config.cameraConfig.bFlipV = configFile["Footfall"]["CameraConfig"]["flipveritcally"].asBool();
		config.cameraConfig.bUseMask = configFile["Footfall"]["CameraConfig"]["usemask"].asBool();
		config.cameraConfig.bShowShadowImage = configFile["Footfall"]["CameraConfig"]["showshadowimage"].asBool();

		vector<ofPoint> pts;
		int maskSize = configFile["Footfall"]["CameraConfig"]["MaskArea"].size();
		for (int i = 0 ; i < maskSize; i++) {
			ofPoint pt = ofPoint(configFile["Footfall"]["CameraConfig"]["MaskArea"][i]["coordx"].asInt(),configFile["Footfall"]["CameraConfig"]["MaskArea"][i]["coordy"].asInt());
			pts.push_back(pt);
		}
		config.cameraConfig.maskCoord = pts;

		//UI Configuration
		config.uiConfig.showhistory = configFile["Footfall"]["UIConfig"]["showhistory"].asBool();
		config.uiConfig.showUI = configFile["Footfall"]["UIConfig"]["showUI"].asBool();

		// Tracking Configuration
		config.trackingConfig.threshold = configFile["Footfall"]["TrackingConfig"]["threshold"].asInt();
		config.trackingConfig.minarea = configFile["Footfall"]["TrackingConfig"]["minarea"].asInt();
		config.trackingConfig.maxarea = configFile["Footfall"]["TrackingConfig"]["maxarea"].asInt();
		config.trackingConfig.startPos = ofPoint(configFile["Footfall"]["TrackingConfig"]["startposx"].asInt(),configFile["Footfall"]["TrackingConfig"]["startposy"].asInt());
		config.trackingConfig.offset = configFile["Footfall"]["TrackingConfig"]["offset"].asInt();
		config.trackingConfig.flipvertically = configFile["Footfall"]["TrackingConfig"]["flipvertically"].asBool();

		config.trackingConfig.persistance = configFile["Footfall"]["TrackingConfig"]["persistance"].asInt();

		config.trackingConfig.history = config.cameraConfig.history;

		config.trackingConfig.blobdyingtime = configFile["Footfall"]["TrackingConfig"]["blobdyingtime"].asFloat();

		config.trackingConfig.minsizeone = configFile["Footfall"]["TrackingConfig"]["minsizeone"].asInt();
		config.trackingConfig.minsizetwo = configFile["Footfall"]["TrackingConfig"]["minsizetwo"].asInt();
		config.trackingConfig.minsizethree = configFile["Footfall"]["TrackingConfig"]["minsizethree"].asInt();
		config.trackingConfig.maxdistance = configFile["Footfall"]["TrackingConfig"]["maxdistance"].asInt();

		config.trackingConfig.showhistory = config.uiConfig.showhistory;

		config.trackingConfig.camerawidth = config.cameraConfig.camerawidth;
		config.trackingConfig.cameraheight = config.cameraConfig.cameraheight;

		// Post Data Settings
		config.mqttConfig.server = configFile["Footfall"]["MQTTConfig"]["server"].asString();
		config.mqttConfig.username = configFile["Footfall"]["MQTTConfig"]["username"].asString();
		config.mqttConfig.password = configFile["Footfall"]["MQTTConfig"]["password"].asString();
		config.mqttConfig.id = configFile["Footfall"]["MQTTConfig"]["id"].asString();
		config.mqttConfig.port = configFile["Footfall"]["MQTTConfig"]["port"].asInt();
		config.mqttConfig.QoS = configFile["Footfall"]["MQTTConfig"]["qos"].asInt();
	}
}

//--------------------------------------------------------------
Configuration ConfigurationManager::getConfiguration()
{
	return config;
}
//--------------------------------------------------------------
void ConfigurationManager::printConfiguration()
{
	cout << configFile.getRawString() << endl;
}

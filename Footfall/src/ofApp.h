// * Name: ofApp.h
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#pragma once

#include "ofMain.h"
#include "ConfigurationManager.h"
#include "CameraManager.h"
#include "TrackingManager.h"
#include "CsvManager.h"
#include "MqttManager.h"


class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();
		void exit();

		ConfigurationManager configManager;
		CameraManager cameraManager;
		TrackingManager trackingManager;
		CsvManager csvManager;
		MqttManager mqttManager;

		void blobIn(int &val);
		void blobOut(int &val);
		void updateResults(int &val);

		bool _logToCsv;
		bool _logToServer;
		int peopleIn;
		int peopleOut;
		int _sequence;
		string _sep;
		string _hostname;
		stringstream _csv_history;
		bool _showUI;
		float _scale;
};

// * Name: ofApp.cpp
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);

	cout << "-------------------- Footfall --------------------" << endl;

	configManager.loadConfiguration("config.json");

	ofSetFrameRate(configManager.getConfiguration().cameraConfig.fps);

	char hostname[HOST_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	_hostname = ofToString(hostname);

	_sequence = 0;
	_sep = ",";

	_logToCsv = configManager.getConfiguration().useCsvLogging;
	_logToServer = configManager.getConfiguration().useMQTT;
	_showUI = configManager.getConfiguration().uiConfig.showUI;

	cameraManager.setup(configManager.getConfiguration().cameraConfig);
	trackingManager.setup(configManager.getConfiguration().trackingConfig);

	cout << "Height " << ofGetWindowHeight() << endl;
	cout << "Width: " << ofGetWindowWidth() << endl;

	if (_logToServer) mqttManager.setup(configManager.getConfiguration().mqttConfig);
	if (_logToCsv) csvManager.setup("csvlogs");

	ofAddListener(trackingManager.blobIn, this, &ofApp::blobIn);
	ofAddListener(trackingManager.blobOut, this, &ofApp::blobOut);
}
//--------------------------------------------------------------
void ofApp::exit()
{
	ofRemoveListener(trackingManager.blobIn, this, &ofApp::blobIn);
	ofRemoveListener(trackingManager.blobOut, this, &ofApp::blobOut);
}
//--------------------------------------------------------------
void ofApp::update()
{
	cameraManager.update();
	trackingManager.update(cameraManager.getImage());
}
//--------------------------------------------------------------
void ofApp::draw()
{
	if (_showUI)
	{
		ofPushMatrix();
		ofScale(2);
		cameraManager.draw();
		trackingManager.draw();
		ofPopMatrix();

		stringstream ss;
		ss << "Footfall" << endl;
		ss << "People In: " << peopleIn;
		ss << " People Out: " << peopleOut << endl;
		ss << "Total: " << (peopleIn+abs(peopleOut));
		ss << " FPS: " << ofGetFrameRate() << endl;

		ofScale(2);
		ofDrawBitmapStringHighlight(ss.str(),650, 20);

		ofScale(0.5);
		ofDrawBitmapStringHighlight(_csv_history.str(),1300, 120);
	}
}
//--------------------------------------------------------------
void ofApp::blobIn(int &val)
{
	peopleIn += val;
	updateResults(val);
}
//--------------------------------------------------------------
void ofApp::blobOut(int &val)
{
	peopleOut += abs(val);
	updateResults(val);
}

void ofApp::updateResults(int &val)
{
	// Blink green LED for 1 second
	system("sudo bash -c 'echo 1 >/sys/class/leds/led0/brightness && sleep 1 && echo 0 >/sys/class/leds/led0/brightness' &");

	string output = ofGetTimestampString("%Y-%m-%d %H:%M:%S") + " | seq " + ofToString(_sequence) + " | ";
	if (val >= 0) output += "+";
	output += ofToString(val) + " blob(s) | " + ofToString(peopleIn+abs(peopleOut)) + " total";

	cout << output << endl;
	_csv_history << output << endl;

	string csv = ofToString(time(0)) + _sep +
									 _hostname + _sep +
									 ofToString(val) + _sep +
									 ofToString(peopleIn+abs(peopleOut)) + _sep +
									 ofToString(_sequence);

	if (_logToServer) mqttManager.publish(csv);
	if (_logToCsv) csvManager.append(csv);

	_sequence++;
}

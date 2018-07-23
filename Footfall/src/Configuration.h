// * Name: Configuration.h
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#ifndef Configuration_h
#define Configuration_h

struct Camera_Configuration
{
	bool useVideoRecording;
	string videoFileName;
	int camerawidth;
	int cameraheight;
	int history;
	int mogThreshold;
	int threshold;
	int dilateAmount;
	int erodeAmount;
	int blur;

	float shadowPixelRatio;

	bool bTrackShadows;
	bool bFlipH;
	bool bFlipV;
	bool bUseMask;
	bool bShowShadowImage;

	vector<ofPoint> maskCoord;
};


struct Tracking_Configuration
{
	int threshold;
	int minarea;
	int maxarea;

	float blobdyingtime;
	int persistance;
	int maxdistance;
	int minsizeone;
	int minsizetwo;
	int minsizethree;
	int history;

	ofPoint startPos;
	ofPoint endPos;
	int camerawidth;
	int cameraheight;

	bool flipvertically;
	int offset;

	bool showhistory;
};

struct MQTT_Configuration
{
	string server;
	string username;
	string password;
	string id;
	int port;
	int QoS;
};

struct UI_Configuration
{
	bool showUI;
	bool vncUI;
	bool showhistory;
};

struct Configuration
{
	bool useMQTT;
	bool useCsvLogging;
	Camera_Configuration cameraConfig;
	Tracking_Configuration trackingConfig;
	MQTT_Configuration mqttConfig;
	UI_Configuration uiConfig;
};

struct Post_Data
{
	Post_Data(string count,string timestamp)
	{
		_count = count;
		_timestamp = timestamp;
	}

	string _count;
	string _timestamp;
};

#endif /* Configuration_h */

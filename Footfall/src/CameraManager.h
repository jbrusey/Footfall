// * Name: CameraManager.h
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#ifndef CameraManager_h
#define CameraManager_h

//#define USE_VIDEO
//#define USE_WEBCAM
//#define USE_PI_CAM

#include <stdio.h>
#include "ofMain.h"
#include "Configuration.h"
#include "ofxCv.h"
#include "ofxCvPiCam.h"

using namespace cv;
using namespace ofxCv;

class CameraManager
{
	public:
		//! Setup
		void setup(Camera_Configuration _cameraConfig);

		//! Update
		void update();

		//! Draw
		void draw();

		//! Get Image
		Mat getImage();

		void placeScreen(Mat screen, int x=0, int y=0, bool full=false, bool border=true, const std::string& caption= std::string());

	private:
//#ifdef USE_WEBCAM
//		ofVideoGrabber videoGrabber;
//#endif

		ofxCvPiCam piCamera;
		ofVideoPlayer videoPlayer;

		Mat videoMatrix;
		Mat processedMog;
		Mat mask;
		Mat combinedMask;
		Mat background;
		Mat unprocessed_MOG;

		BackgroundSubtractorMOG2 *pMOG2;

		vector<cv::Point> _maskPts;
		bool _useVideoRecording;
		bool _useMask;
		bool _showShadows;
		int _threshold;
		int _dilateAmount;
		int _erodeAmount;
		int _blur;
};

#endif /* CameraManager_h */

// * Name: CameraManager.cpp
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#include "CameraManager.h"
//--------------------------------------------------------------
void CameraManager::setup(Camera_Configuration _cameraConfig)
{
	cout << "Setting Up Camera Manager";
	_useMask = _cameraConfig.bUseMask;
	_useVideoRecording = _cameraConfig.useVideoRecording;

	// Check whether the mask should be generated
	if (_useMask)
	{
		// Get the Mask Coordinates
		for (int i = 0; i < _cameraConfig.maskCoord.size(); i++)
		{
			cv::Point p = cv::Point(_cameraConfig.maskCoord[i].x,_cameraConfig.maskCoord[i].y);
			_maskPts.push_back(p);
		}

		mask = cvCreateMat(_cameraConfig.cameraheight, _cameraConfig.camerawidth, CV_8UC1);
		combinedMask = cvCreateMat(_cameraConfig.cameraheight, _cameraConfig.camerawidth, CV_8UC1);

		// Fill the Mat with black
		for(int i=0; i<mask.cols; i++)
			for(int j=0; j<mask.rows; j++)
				mask.at<uchar>(cv::Point(i,j)) = 0;

		vector<cv::Point> polyright;
		approxPolyDP(_maskPts, polyright, 1.0, true);
		fillConvexPoly(mask,&polyright[0],polyright.size(),255,8,0);
	}

	// Setup the Background MOG2
	pMOG2 = new BackgroundSubtractorMOG2(_cameraConfig.history,
										 _cameraConfig.mogThreshold,
										 _cameraConfig.bTrackShadows
										 );
	// This is the ratio of the shadow detection. I.e how many times lighter the shadow needs to be to be considered a blob.
	pMOG2->setDouble("fTau", _cameraConfig.shadowPixelRatio);

	if (_useVideoRecording)
	{
		cout << " - Using Video" << endl;
		videoPlayer.load(_cameraConfig.videoFileName);
		videoPlayer.setLoopState(OF_LOOP_NORMAL);
		videoPlayer.play();
	}
	else
	{
		cout << " - Using Pi Camera" << endl;
		piCamera.setup(_cameraConfig.camerawidth,_cameraConfig.cameraheight,true);
		piCamera.setFlips(_cameraConfig.bFlipH,_cameraConfig.bFlipV);
	}
	/*
	#ifdef USE_WEBCAM
		cout << " - Using Web Camera" << endl;
		videoGrabber.setVerbose(true);
		videoGrabber.setup(_cameraConfig.camerawidth, _cameraConfig.cameraheight);
	#endif
	*/

	_threshold = _cameraConfig.threshold;
	_showShadows = _cameraConfig.bShowShadowImage;
	_dilateAmount = _cameraConfig.dilateAmount;
	_erodeAmount = _cameraConfig.erodeAmount;
	_blur = _cameraConfig.blur;
}
//--------------------------------------------------------------
void CameraManager::update()
{
	if (_useVideoRecording)
	{
		videoPlayer.update();

		if (videoPlayer.isFrameNew())
		{
			copy(videoPlayer, videoMatrix);
		}
	}
	else
	{
		videoMatrix = piCamera.grab();
	}
	/*
	#ifdef USE_WEBCAM
		videoGrabber.update();

		if (videoGrabber.isFrameNew())
		{
			copy(videoGrabber, videoMatrix);
		}
	#endif
	*/
	if (!videoMatrix.empty())
	{
		// Blur the original image
		GaussianBlur(videoMatrix, _blur);

		// Process the MOG
		if (_useMask)
		{
			videoMatrix.copyTo(combinedMask, mask);
			pMOG2->operator()(combinedMask,processedMog);
		}
		else
		{
			pMOG2->operator()(videoMatrix,processedMog);
		}

		// Get the background image
		pMOG2->getBackgroundImage(background);

		// If you want to see the effect of the shadow ratio threshold. Set the showshadow config to true
		// Copy the MOG's output before processing the mat

		if(_showShadows) copy(processedMog,unprocessed_MOG);

		// Image processing
		threshold(processedMog,_threshold);
		blur(processedMog,_blur);
		dilate(processedMog,_dilateAmount);
		erode(processedMog,_erodeAmount);
		dilate(processedMog,_dilateAmount);
		GaussianBlur(processedMog, _blur*2);

		// Leave these two
		threshold(processedMog,50);
		erode(processedMog,2);
	}
}
//--------------------------------------------------------------
void CameraManager::draw()
{
	ofPushMatrix();
	//ofSetColor(255, 255, 255);

	//ofFill();
	//ofDrawRectangle(0, 0, videoMatrix.cols+1,videoMatrix.rows+1);
	//ofDrawRectangle(videoMatrix.cols -1, 0, videoMatrix.cols+1,videoMatrix.rows+1);
	//ofDrawRectangle(videoMatrix.cols -1, videoMatrix.rows+29, videoMatrix.cols + 2,videoMatrix.rows + 2);
	//ofDrawRectangle(0, videoMatrix.rows+29,videoMatrix.cols+2,videoMatrix.rows+2);

	//drawMat(videoMatrix, 0, 0,videoMatrix.cols,videoMatrix.rows);
	placeScreen(videoMatrix, "Input Image", 0, 0, false, true);
	//placeScreen(background, "Background", 1, 0, false, true);
	//placeScreen(unprocessed_MOG, "Shadows Image", 0, 1, false, true);
	//placeScreen(processedMog, "Processed Image", 1, 1, false, true);
	//drawMat(background, videoMatrix.cols, 0,videoMatrix.cols,videoMatrix.rows);
	//ofDrawBitmapStringHighlight("Input Image", (videoMatrix.cols/2)-45,videoMatrix.rows+20);
	//ofDrawBitmapStringHighlight("Background", ((videoMatrix.cols/2)*3)-65,videoMatrix.rows+20);
	//drawMat(unprocessed_MOG, videoMatrix.cols, videoMatrix.rows+30,videoMatrix.cols,videoMatrix.rows);
	//ofDrawBitmapStringHighlight("Shadows Image", ((videoMatrix.cols/2)*3)-45,(videoMatrix.rows*2)+50);
	//drawMat(processedMog, 0, videoMatrix.rows+30,videoMatrix.cols,videoMatrix.rows);
	//ofDrawBitmapStringHighlight("Processed Image", (videoMatrix.cols/2)-45,(videoMatrix.rows*2)+50);
	ofPopMatrix();
}
//--------------------------------------------------------------
Mat CameraManager::getImage()
{
	return processedMog;
}

void CameraManager::placeScreen(Mat screen, std::string caption, int x, int y, bool full, bool border)
{
	cout << "Place screen started" << endl;
	if (full)
		drawMat(screen, 0, 0, screen.cols*2, screen.rows*2);
		if (caption != "") ofDrawBitmapStringHighlight(caption, 0, 0);
	else
	{
		int startX;
		int startY;
		int sizeX;
		int sizeY;

		if (x==0) {
			startX = 0;
			sizeX = screen.cols;
			cout << "X set to 0" << endl;
		}
		else {
			startX = screen.cols;
			sizeX = screen.cols*2;
		}

		if (y == 0) {
			cout << "Y set to 0" << endl;
			startY = 0;
			sizeY = screen.rows;
		}
		else {
			startY = screen.rows;
			sizeY = screen.cols*2;
		}

		drawMat(screen, startX, startY, sizeX, sizeY);
		cout << "Screen placed" << endl;
		//if (caption != "") ofDrawBitmapStringHighlight(caption, startX, startY);
	}
}

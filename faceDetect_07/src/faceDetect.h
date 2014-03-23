/*
 *  faceDetect.h
 *  faceDetect04
 *
 *  Created by Joe Saavedra on 2/13/11.
 *  Copyright 2011 Parsons The New School for Design. All rights reserved.
 *
 */

#ifndef _THREADED_OBJECT
#define _THREADED_OBJECT

#include "ofMain.h"
#include "ofxThread.h"
#include "ofxCvHaarFinder.h"
#include "ofxOpenCv.h"

class faceDetect : public ofxThread{
	
public:	
	
	faceDetect();

	ofxCvHaarFinder			finder;
	int						cam_width, cam_height;
	int						track_width, track_height;
	ofxCvColorImage			camImg;
	ofxCvColorImage			trackImg;
	ofxCvGrayscaleImage		trackImg_gray;
	ofVideoGrabber			vidGrabber;
	int						framecounter;
	float					tracker_fps;
	int						frame_timestamp;

	void start();
	void stop();
	void draw();
	void update();
	void setup();
	void threadedFunction();
	void getCamSettings(bool);
	
	
	bool faceDetected();
	
	int blobsFound;
	
};

#endif
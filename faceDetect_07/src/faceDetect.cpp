/*
 *  faceDetect.cpp
 *  faceDetect04
 *
 *  Created by Joe Saavedra on 2/13/11.
 *  Copyright 2011 Parsons The New School for Design. All rights reserved.
 *
 */

#include "faceDetect.h"
//#include "ofxThread.h"
//#include "ofxCvHaarFinder.h"
//#include "ofxOpenCv.h"

//--------------------------
faceDetect::faceDetect(){

}
	
void faceDetect::setup(){	
	// setup tracker - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	finder.setup("haarcascade_frontalface_default.xml");
	cam_width = 640; cam_height = 480;
	track_width = 320; track_height = 240;

	vidGrabber.initGrabber(cam_width, cam_height);
	
	vidGrabber.setUseTexture(false);
	camImg.allocate(cam_width, cam_height);
	camImg.setUseTexture(false);
	trackImg.allocate(track_width, track_height);
	trackImg.setUseTexture(false);
	trackImg_gray.allocate(track_width, track_height);
	trackImg_gray.setUseTexture(false);
	finder.findHaarObjects(trackImg_gray);
	tracker_fps = 0;
	framecounter = 0;
	frame_timestamp = ofGetElapsedTimeMillis();
	
	blobsFound = 0;

}
void faceDetect::update(){
	
	//blobsFound = finder.blobs.size();
	
}

void faceDetect::start(){
	startThread(true, false);   // blocking, verbose
}

void faceDetect::stop(){
	stopThread();
}

//--------------------------
void faceDetect::threadedFunction(){
	
	while( isThreadRunning() != 0 ){
		//if( lock() ){
		
		if(	ofGetElapsedTimeMillis() > frame_timestamp + 500) {
			tracker_fps = (float) framecounter * 1000 / (ofGetElapsedTimeMillis()-frame_timestamp);
			framecounter = 0;
			frame_timestamp = ofGetElapsedTimeMillis();
		}
		
		
		vidGrabber.grabFrame();
		
		if (vidGrabber.isFrameNew())
		{		
			camImg = vidGrabber.getPixels();
			camImg.mirror(false, true);
			trackImg.scaleIntoMe(camImg);
			trackImg_gray = trackImg;
			finder.findHaarObjects(trackImg_gray);
		}
		
		
		//unlock();
		framecounter ++;
		ofSleepMillis(10);
		//}
	}
}

//--------------------------
void faceDetect::draw(){
	
	string str = "";
	

	
	if( lock() ){
		
		ofNoFill();
		
		glPushMatrix();
		
		glScalef(cam_width/track_width, cam_width/track_width, cam_width/track_width);
		for(int i = 0; i < finder.blobs.size(); i++) {
			ofRectangle cur = finder.blobs[i].boundingRect;
			ofRect(cur.x, cur.y, cur.width, cur.height);
		}
		glPopMatrix();
		
		unlock();
	}else{
		str = "can't lock!\neither an error\nor the thread has stopped";
	}
	ofDrawBitmapString(str, 50, 56);
}

//----------------------------

bool faceDetect::faceDetected(){
	
	if ( finder.blobs.size() > 0) {
		return true;
	} else {
		return false;
	}	
}

void faceDetect::getCamSettings(bool settingsUp){
	
	if (settingsUp) {
		vidGrabber.videoSettings();
	}
}

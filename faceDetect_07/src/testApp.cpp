#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// setup application - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	ofSetVerticalSync(true);
	//ofEnableAlphaBlending();
		
	camImg.allocate(640, 480);
	
	TO.setup();
	TO.start();
	locked = false;
	timerFlag = true;
	bufferTime = 500; //how long to wait before showing movie
	lastHit = 0;
	
	deBuggz = false;
	
	movie.loadMovie("movies/rumi1.mov");
	//movie.setUseTexture(false);
	movie.play();
	noise.loadMovie("movies/noise5.mov");
	//noise.setUseTexture(false);
	noise.play();
}

//--------------------------------------------------------------
void testApp::update(){

	if(deBuggz){
		camImg = TO.vidGrabber.getPixels();
		camImg.mirror(false, true);
	}
	
	if(TO.faceDetected() == true){ //FACE TIME :: noise vid
		locked = true;
		lastHit = ofGetElapsedTimeMillis();
		
		movie.setPaused(true);
		noise.setPaused(false);

		timerFlag = false;
		
	} else if (TO.faceDetected() == false && timerFlag == true){ //NO FACE :: movie vid
		locked = false;
		
		movie.setPaused(false);
		noise.setPaused(true);
		
		timerFlag = false;
	}
	
	if (ofGetElapsedTimeMillis() - lastHit > bufferTime) {
		timerFlag = true;
		
	}
	
	movie.idleMovie();
	noise.idleMovie();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
	//trackImg_gray.draw(track_width, cam_height);
	ofSetColor(0xffffff);
	
	//movie.draw(0, 0);
	if(!deBuggz){
		
		if (locked==0) {	// NO FACE
			movie.draw(0,0,1920,1080);
			
			ofFill();
			ofSetColor(0, 0, 0);
			ofRect(0, 0, 200, 80);
			ofSetColor(255, 255, 255);
			ofDrawBitmapString("NO FACE", 20, 65);
		} 
		else {			// FACE TIME
			noise.draw(0,0,1920,1080);
			
			ofSetColor(255, 255, 255);
			ofDrawBitmapString("noise static noise", ofGetWidth()/2, ofGetHeight()/2);
			
			ofFill();
			ofSetColor(0, 0, 0);
			ofRect(0, 0, 200, 80);
			ofSetColor(255, 255, 255);
			ofDrawBitmapString("I SEE YOU", 20, 65);
		}
	}
	
	if(deBuggz){
		ofSetColor(0xffffff);
		camImg.draw(0, 0);
		TO.draw();
	}

	ofSetColor(255, 255, 255);
	string info = "";
	info += "app fps: "+ofToString(ofGetFrameRate(), 2);
	info += "\ntracker fps: "+ofToString(TO.tracker_fps, 2);
	//info += "\nmovie fps: "+ofToString(movie., <#int precision#>)   ;
	ofDrawBitmapString(info, 20, 32);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'd') {
		deBuggz = !deBuggz;
	}
	if (key == 'c'){
		camSettings = true;
		TO.getCamSettings(camSettings);	
		camSettings = false;
		
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}



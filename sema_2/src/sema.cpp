#include "sema.h"

//--------------------------------------------------------------
void sema::setup(){
    cameraOn = true;

    //print out a list of all camera devices
	vector<ofVideoDevice> devices = vidGrabber1.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}

    deviceID = 0; //change this when there is an external camera attached
    vidGrabber1.setVerbose(true);
    vidGrabber1.setDeviceID(deviceID); //use this when there is an external camera attached (find number in log)
	vidGrabber1.initGrabber(320,240,false);

    colorImage1.allocate(320,240);
	grayImage1.allocate(320,240);
    
    // load the correct xml file from the bin/data/haarXML/ folder
	haarFinder1.setup("haarXML/haarcascade_frontalface_default.xml");
    
    deBuggz = true;
    iSeeYou = true;
    bufferTime = 2.0f;
    scaleHaar = 1.25f;
	
	ofBackground(0,0,0);
    
    video1.loadMovie("videos/video1.mov");
    video1.play();
    noise.loadMovie("videos/noise.mov");
    noise.play();
}

//--------------------------------------------------------------
void sema::update(){
    
    video1.update();
    noise.update();
    vidGrabber1.update();
    
	haarFinder1.setScaleHaar(scaleHaar);
    
    bool bNewFrame = false;
    
    if(cameraOn == true){
        if (vidGrabber1.isFrameNew()){
            colorImage1.setFromPixels(vidGrabber1.getPixels(), 320,240);
            grayImage1 = colorImage1;
            haarFinder1.findHaarObjects(grayImage1);
        }
    }
    if(iSeeYou){ //face has been detected
        video1.setPaused(true);
        noise.setPaused(false);
    }else{
        video1.setPaused(false);
        noise.setPaused(true);
    }
}

//--------------------------------------------------------------
void sema::draw(){
    
    // how many matches did you find?
	int numMatches = haarFinder1.blobs.size();
    
    if(numMatches > 0){
        faceDetected(TRUE);
    }else{
        faceDetected(FALSE);
    }
    
    if (iSeeYou){
        noise.draw(0,0,ofGetWidth(),ofGetHeight());
    }else{
        video1.draw(0,0,ofGetWidth(),ofGetHeight());
    }    
    
    if(deBuggz){
        // info bg
        ofFill();
        ofSetColor(0);
        ofRect(20,0,320,355);
        
        // draw the incoming & the grayscale
        ofSetColor(255);
        colorImage1.draw(20,80);	
        //grayImage1.draw(360,20);
        
        // drawing the matches
        glPushMatrix();
        glTranslatef(20, 80, 0);
        for(int i = 0; i < numMatches; i++){
            float x = haarFinder1.blobs[i].boundingRect.x;
            float y = haarFinder1.blobs[i].boundingRect.y;
            float w = haarFinder1.blobs[i].boundingRect.width;
            float h = haarFinder1.blobs[i].boundingRect.height;
            
            float cx = haarFinder1.blobs[i].centroid.x;
            float cy = haarFinder1.blobs[i].centroid.y;
            
            ofSetColor(0x00FF00);
            ofSetLineWidth(4);
            ofNoFill();
            ofEllipse(x+w/2, y+h/2, w, 4*h/3);
            
            ofSetColor(0xFFFFFF);
            ofDrawBitmapString(ofToString(i), cx, cy);
            
        }
        glPopMatrix();
        
        ofSetLineWidth(1);
        
	
        // drawing some info
        int numMess = 1;
        string reportStr= "faces found: "+ ofToString(numMatches, 0)+" || framerate: "+ofToString(ofGetFrameRate(),0);
        string haarReportStr= "haar scaling: "+ ofToString(scaleHaar) +" || CamID: "+ofToString(deviceID);
        string setupInfo = "** Hit '3' to init first cam device";
        string setupInfo2 = "** Hit '4' to init second cam device";
        string setupInfo3 = "** Hit 'F' for Fullscreen";
        string setupInfo4 = "** Hit 'D' to toggle Debuggz";
        string setupInfo5 = "** Hit 'THEBOTTLE' hard";
        
        ofDrawBitmapString(setupInfo, 40, 15*numMess);
        ofDrawBitmapString(setupInfo2, 40, 30*numMess);
        ofDrawBitmapString(setupInfo3, 40, 45*numMess);
        ofDrawBitmapString(setupInfo4, 40, 60*numMess);
        ofDrawBitmapString(setupInfo5, 40, 75*numMess);
        ofDrawBitmapString(reportStr, 40, 335*numMess);
        ofDrawBitmapString(haarReportStr, 40, 350*numMess);
    }
    //cout<<"mouseX: "<< mouseX << "mouseY: << mouseY << endl;

}

//--------------------------------------------------------------
void sema::keyPressed(int key){
    switch (key){
            
        case '3':
            cameraOn = false;
            vidGrabber1.close();
            deviceID = 3;
            vidGrabber1.setDeviceID(deviceID);
            vidGrabber1.initGrabber(320,240,false);
            cameraOn = true;
            break;
            
        case '4':
            cameraOn = false;
            vidGrabber1.close();
            deviceID = 3;
            vidGrabber1.setDeviceID(deviceID);
            vidGrabber1.initGrabber(320,240,false);
            cameraOn = true;
            break;            
            
		case 's':
			vidGrabber1.videoSettings();
            break;
            
        case 'd':
            deBuggz = !deBuggz;
            break;
        
        case 'f':
            ofToggleFullscreen();
            break;
        
        case 'l':
            vidGrabber1.listDevices();
            break;
        
            
        case OF_KEY_UP:
            cameraOn = false;
            vidGrabber1.close();
            deviceID += 1;
            vidGrabber1.setDeviceID(deviceID);
            vidGrabber1.initGrabber(320,240,false);
            cameraOn = true;
            break;
        
        case OF_KEY_DOWN:
            cameraOn = false;
            vidGrabber1.close();
            deviceID -= 1;
            vidGrabber1.setDeviceID(deviceID);
            vidGrabber1.initGrabber(320,240,false);
            cameraOn = true;
            break;
            
        case OF_KEY_RIGHT:
            if(scaleHaar >= 1.2f){
                scaleHaar -= 0.05f;
            }else{
                scaleHaar =1.1f;
            }
            break;
            
        case OF_KEY_LEFT:
            scaleHaar +=0.05f;
            break;
            
	}
}

//--------------------------------------------------------------
void sema::faceDetected(bool detected){
    
    if(detected){
        iSeeYou = true;

    }
    
    else{
        float currTime = ofGetElapsedTimef();
        if (currTime - lastDetect > bufferTime) {
            iSeeYou = false;
            lastDetect = ofGetElapsedTimef();
        }
    }
}

//--------------------------------------------------------------
void sema::keyReleased(int key){

}

//--------------------------------------------------------------
void sema::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void sema::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void sema::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void sema::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void sema::windowResized(int w, int h){

}


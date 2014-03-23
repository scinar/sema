#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "ofxOpenCv.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
    
    
    ofVideoGrabber 		vidGrabber1;
    ofVideoGrabber 		vidGrabber2;
    
    ofxCvColorImage			colorImage1;
    
    ofxCvGrayscaleImage 	grayImage1;
    
    ofxCvHaarFinder			haarFinder1;

    
    float scaleHaar;
    
    ofVideoPlayer 		video1;
    ofVideoPlayer       noise;
    
    bool deBuggz;
    bool iSeeYou;
    
    void faceDetected(bool detected);
    float lastDetect;
    float bufferTime;
    
    int deviceID;
    bool cameraOn;

};

#endif

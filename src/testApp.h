#pragma once

#include "ofMain.h"
#include "ofxAnimatable.h"
#include "ofxOsc.h"
#include "ofxFX.h"
#include "ofxFXObject.h"

#include "faceController.h"
#include "MachineMapping2D.h"

// listen on port 12345
#define PORT 12345

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);


    void scene();
    ofxOscReceiver receiver;

    MachineMapping2D *northMapping, *eastMapping, *southMapping;
    faceController fController;

};

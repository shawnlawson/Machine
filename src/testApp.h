#pragma once

#include "ofMain.h"
#include "ofxAnimatable.h"
#include "ofxOsc.h"
#include "ofxFX.h"
#include "ofxFXObject.h"
#include "ofxXmlSettings.h"

#include "BlackScreen.h"
#include "MyGrid.h"
#include "PolygonEDF0.h"
#include "faceController.h"
#include "MachineMapping2D.h"

// listen on port 12345
#define PORT 12345

enum moveMapping{
    zero,
    north,
    east,
    south
};

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
    void nudgeMappings( int direction );
    void myLoadSettings();
    
    ofxOscReceiver receiver;

    BlackScreen     blackScreen;
    MyGrid          grid;
    MachineMapping2D *northMapping, *eastMapping, *southMapping;
    faceController fController;
    
    moveMapping myMoveMapping;

    ofVec2f northPos, eastPos, southPos;
    bool    drawBackground, fullscreen;
    
    ofxXmlSettings XML;
    
    bool    myZoom;
    
    PolygonEDF0 *edf0;
    	ofVec2f startingNodes[6];
    
   
};

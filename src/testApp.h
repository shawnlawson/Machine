#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#include "BlackScreen.h"
#include "MyGrid.h"
#include "PolygonController.h"
#include "faceController.h"
#include "Banner.h"
#include "AnimatedGrid.h"
#include "MachineMapping2D.h"

// listen on port 12345
#define PORT 12345
#define LONG_WALL 3640
#define SHORT_WALL 2990
#define HEIGHT_WALL 780


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


    void scene( int leftSide, float time );
    void nudgeMappings( int direction );
    void myLoadSettings();
    
    ofxOscReceiver receiver;

    BlackScreen     blackScreen;
    MyGrid          grid;
    PolygonController     pController;
    
    MachineMapping2D *northMapping, *eastMapping, *southMapping;
    faceController fController;
    
    Banner *banner;
    AnimatedGrid *aGrid;
    
    moveMapping myMoveMapping;

    ofVec2f northPos, eastPos, southPos;
    bool    drawBackground, fullscreen;
    
    ofxXmlSettings XML;
    
    bool    myZoom;
    
    
   
};

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxUI.h"

#include "MyConstants.h"
#include "BlackScreen.h"
#include "PolygonController.h"
#include "faceController.h"
#include "Banner.h"
#include "AnimatedGrid.h"
#include "MachineMapping2D.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);


    void scene( int leftSide, int width, float time );
    void buildGUI();


    BlackScreen     blackNorthWest, blackNorthEast, blackEast, blackSouthEast, blackSouthWest;
    PolygonController     pController;
    
    MachineMapping2D *northMapping, *eastMapping, *southMapping;
    faceController fController;
    
    Banner *banner;
    AnimatedGrid *aGrid;

    ofPoint northPos, eastPos, southPos;
    bool    drawBackground, fullscreen;
    
    
    ofxUICanvas *gui, *gui2, *gui3;
	void guiEvent(ofxUIEventArgs &e);

    ofxXmlSettings XML;
    
    bool    myZoom, bInit;
    
    
   
};

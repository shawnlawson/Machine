#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxUI.h"

#include "MyConstants.h"
#include "BlackScreen.h"
#include "PolygonController.h"
#include "faceController.h"
#include "Banner.h"
#include "GameOfLife.h"
#include "AnimatedGrid.h"
#include "Joanna.h"
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
    GameOfLife *northGame, *eastGame, *southGame;
    
    Joanna joanna;
    
    float aGridDur, aGridWaveDur, ravenDur, faceWhiteDur, faceVertexDur, faceRandomDur, jWhiteDur, jVertexDur, jRandomDur, faceReEmergeDur, jRandomOutDur, GOLDur;

    ofPoint northPos, eastPos, southPos;
    bool    drawBackground, fullscreen, bBannerOn, bGridOn, bRavenOn, bGameOn, bFacesOn, bJoannaOn, bPixelateOn, facesLoading;
    
    ofShader pixelate;
    float pixelSize;
    
    ofxUICanvas *gui, *gui2, *gui3, *gui4;
	void guiEvent(ofxUIEventArgs &e);

    ofxXmlSettings XML;
    
    bool    myZoom;
    
    
   
};

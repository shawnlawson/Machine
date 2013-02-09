//
//  PolygonController.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/4/13.
//
//


#pragma mark once
#include "ofMain.h"

#include "PolygonEDF0.h"

class PolygonController : public ofNode{
public:
    ofPoint         startingNodes[6];
    PolygonEDF0     *edf0;
    ofFbo           polyFbo;
    
    PolygonController(){
        for(int i=0;i<6;i++){
            float x = cos(ofDegToRad(i*60.0f))*350.0f; //radius of hexagon
            float y = sin(ofDegToRad(i*60.0f))*350.0f; //radius of hexagon
            startingNodes[i] = ofPoint(x,y);
        }
        
         edf0 = new PolygonEDF0(0,0,3); // , , recursive maxLevel
        
        polyFbo.allocate(780, 780);

    }
    
    void update(){
        edf0->update(startingNodes, ofGetFrameNum()*0.01f);
        
        polyFbo.begin();

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //    ofClear(0.0, 0.0, 0.0, 0.0);
        ofClear(0.0f, 0.0f, 0.0f, 0.0f);
     //   ofClearAlpha();
      //  ofClear(1.0, 1.0, 1.0, 0.0);
//        ofSetColor(0, 0, 0, 255);
 //       ofRect(0, 0, polyFbo.getWidth(), polyFbo.getHeight());
        ofSetColor(255, 255, 255, 128);
        ofPushMatrix();
        ofTranslate(polyFbo.getWidth()/2,polyFbo.getHeight()/2);
        edf0->draw();
        ofPopMatrix();

        ofDisableAlphaBlending();
        
        polyFbo.end();
    }
    
    void draw(){
        ofSetColor(255);
        polyFbo.draw(0, 0);
        
        polyFbo.draw(780, 0);
        polyFbo.draw(780*2, 0);
                polyFbo.draw(780*3, 0);
                polyFbo.draw(780*4, 0);
    }
    
};

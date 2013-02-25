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


class myNode:public ofNode
{
public:
    ofxAnimatableFloat alpha;
    int frame;
};

class PolygonController
{
public:
    ofPoint         startingNodes[6];
    PolygonEDF0     *edf0;
    ofFbo           polyFbo[NUM_FRAMES];
    vector<myNode>  nodes;
    int whichFrame;
    
    PolygonController(){
        whichFrame = 0;
        
        for(int i=0;i<6;i++){
            float x = cos(ofDegToRad(i*60.0f))*295.0f; //radius of hexagon
            float y = sin(ofDegToRad(i*60.0f))*295.0f; //radius of hexagon
            startingNodes[i] = ofPoint(x,y);
        }
        
         edf0 = new PolygonEDF0(0,0,3); // , , recursive maxLevel
        
        for (int i =0; i<NUM_FRAMES; i++) {
            polyFbo[i].allocate(520, 520, GL_RGBA, 4);
            polyFbo[i].setAnchorPercent(0.5f, 0.5f);
        }

        for(int i= 0; i<10; i++){
            myNode n;
            n.alpha.reset(0.0);
            n.setPosition(i*520 + 520 + i*520, 520, 0);
            n.frame = (int)ofRandom(NUM_FRAMES-5);
            nodes.push_back(n);
        }

        for (int i=0; i<NUM_FRAMES-1; i++) {
            update(0, 0.0);
        }
    }
    
    void update(int showState, float dt){
        edf0->update(startingNodes, ofGetFrameNum()*0.01f);
        
        polyFbo[whichFrame].begin();

       // ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofClear(0.0f, 0.0f, 0.0f, 0.0f);
        ofSetColor(255, 255, 255, 196);
        ofPushMatrix();
        ofTranslate(polyFbo[whichFrame].getWidth()/2,
                    polyFbo[whichFrame].getHeight()/2);
        edf0->draw();
        ofPopMatrix();

      //  ofDisableAlphaBlending();
        
        polyFbo[whichFrame].end();
        
        whichFrame += 1;
        whichFrame %= NUM_FRAMES;

        for (int i=0; i<nodes.size(); i++) {
     //       nodes[i].rotate(.1, 0, 0, 1);
            nodes[i].alpha.update(dt);
            nodes[i].frame += 1;
            nodes[i].frame %= NUM_FRAMES;
        }
        
        switch (showState)
        {
            //all transparent now
            case 2:
                for (int i=0; i<nodes.size(); i++) {
                    nodes[i].alpha.reset(0.0);
                }
                break;

            //all opaque now
            case 3:
                for (int i=0; i<nodes.size(); i++) {
                    nodes[i].alpha.reset(1.0);
                }
                break;
                
            //random start fade in
            case 4:
                for(int i=0; i<nodes.size(); i++){
                    nodes[i].alpha.reset(0.0);
                    nodes[i].alpha.animateToAfterDelay(1.0f, ofRandom(60.0));
                }
                break;
                
            //random start fade out
            case 5:
                for(int i=0; i<nodes.size(); i++){
                    nodes[i].alpha.reset(1.0);
                    nodes[i].alpha.animateToAfterDelay(0.0f, ofRandom(60.0));
                }
                break;
                
            //gradually fade all transparent
            case 6:
                for (int i=0; i<nodes.size(); i++) {
                    nodes[i].alpha.reset(1.0f);
                    nodes[i].alpha.animateFromTo(1.0f, 0.0f);
                }
                break;

            //gradually fade all opaque
            case 7:
                for (int i=0; i<nodes.size(); i++) {
                    nodes[i].alpha.reset(0.0f);
                    nodes[i].alpha.animateFromTo(0.0f, 1.0f);
                }
                break;
                
            default:
                    break;
        }

    }
    
    void draw()
    {
        for (int i=0; i<nodes.size(); i++) {
            ofSetColor(255, 255, 255, nodes[i].alpha.val()*255);
            nodes[i].transformGL();
            polyFbo[nodes[i].frame].draw(0, 0);
            nodes[i].restoreTransformGL();
        }
    }
    
};

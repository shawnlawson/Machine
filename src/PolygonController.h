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
    float timeScaler;
    
    PolygonController(){
        whichFrame = 0;
        timeScaler = 0.01;
        
        for(int i=0;i<6;i++){
            float x = cos(ofDegToRad(i*60.0f))*275.0f; //radius of hexagon
            float y = sin(ofDegToRad(i*60.0f))*275.0f; //radius of hexagon
            startingNodes[i] = ofPoint(x,y);
        }
        
         edf0 = new PolygonEDF0(0,0,3); // , , recursive maxLevel
        
        for (int i =0; i<NUM_FRAMES; i++) {
            polyFbo[i].allocate(TILE_SIZE*4, TILE_SIZE*4, GL_RGBA, 4);
            polyFbo[i].setAnchorPercent(0.5f, 0.5f);
        }

        for(int i= 0; i<10; i++){
            myNode n;
            n.alpha.reset(0.0);
            n.setPosition(i*887.5 +887.5/2, TILE_SIZE*4, 0);
            n.setScale(0.0);
            n.roll(ofRandom(100));
            n.frame = (int)ofRandom(NUM_FRAMES-5);
            nodes.push_back(n);
        }

        for (int i=0; i<NUM_FRAMES-1; i++) {
            update(0, 0.0);
        }
    }
    
    void assignAlpha(float newAlpha){
        for (int i=0; i<nodes.size(); i++) {
            nodes[i].alpha.reset(newAlpha);
        }
    }

    void assignLength(float newDuration){
        for (int i=0; i<nodes.size(); i++) {
            nodes[i].alpha.setDuration(newDuration);
        }
    }
    
    void fadeOut()
    {
        for (int i=0; i<nodes.size(); i++) {
            nodes[i].alpha.animateTo(0.0);
        }
    }
    
    void fadeIn()
    {
        for (int i=0; i<nodes.size(); i++) {
            nodes[i].alpha.animateTo(1.0);
        }
    }
    
    void fadePartial(float newAlpha)
    {
        for (int i=0; i<nodes.size(); i++) {
            nodes[i].alpha.animateTo(newAlpha);
        }
    }
    
    void randomFadeIn( float minDuration, float maxDuration){
        for(int i=0; i<nodes.size(); i++){
            nodes[i].alpha.animateToAfterDelay(1.0f,
                                               ofRandom(minDuration, maxDuration));
        }
    }
    
    void update(int showState, float dt){
        edf0->update(startingNodes, ofGetFrameNum() * timeScaler);
        
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
            nodes[i].setScale(nodes[i].alpha.val());
            nodes[i].roll(0.06);
            nodes[i].move(5, 0.0, 0.0);
            if(nodes[i].getX() > LONG_WALL*2+SHORT_WALL+887.5/2){
                nodes[i].setPosition( -887.5/2, TILE_SIZE*4, 0);
                cout << nodes[i].getX() << endl;
            }
            
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

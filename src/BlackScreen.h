//
//  BlackScreen.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/3/13.
//
//
#pragma mark once
#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class BlackScreen{

public:
    ofxAnimatableFloat alpha;
    
    BlackScreen(){
        alpha.reset(255);
        alpha.setDuration(5.0f);
    }
   
    void fadeOut(){
        alpha.animateTo(0);
    }
    
    void fadeIn(){
            alpha.animateTo(255);
    }
    
    void draw( float dt ){
        if(alpha.isAnimating())
            alpha.update( dt );
        
        ofSetColor(0, 0, 0, alpha.val());
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
};
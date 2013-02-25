//
//  BlackScreen.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/3/13.
//
//
#pragma once
#include "ofMain.h"

#include "ofxAnimatableFloat.h"

class BlackScreen{

public:
    ofxAnimatableFloat alpha;
    
    BlackScreen(){
        alpha.reset(0.0);
        alpha.setDuration(5.0f);
    }
   
    void fadeOut(){
        alpha.animateTo(0);
    }
    
    void fadeIn(){
        alpha.animateTo(255);
    }
    
    void fadePartial(float newAlpha){
        alpha.animateTo(newAlpha);
    }
    
    void draw( float dt , int x, int y){
        alpha.update( dt );
        
        ofSetColor(0, 0, 0, alpha.val());
        ofRect(x, y, 1920, 1080);
    }
    
};
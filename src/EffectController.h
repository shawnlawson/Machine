//
//  EffectController.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/9/13.
//
//

#pragma mark once
#include "ofMain.h"

class EffectController{
public:
    //vector <face> shaders;
    
    ofxAnimatableFloat f;
    
    ofShader shader;
    
    EffectController(){
        f.setRepeatType(LOOP_BACK_AND_FORTH);
        f.animateFromTo(0.0, 11.0);
    }
    
    void loadShaders(){
         shader.load("shaders/shader27");
        
        
    }
    
    
void update(){
    
}

void draw(int offsetX, int offsetY, float time){
    f.update(ofGetLastFrameTime()*.01);
    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef()*0.1);
    shader.setUniform1f("lineSize", f);
    shader.setUniform2f("resolution", offsetX, offsetY);
//   transformGL();
//    ofSetColor( 255, 255, 255, 255);
   
//    restoreTransformGL();
    ofRect(offsetX, 0, 3640, 780);
    shader.end();
}
    
};
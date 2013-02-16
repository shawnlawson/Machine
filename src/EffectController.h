//
//  EffectController.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/9/13.
//
//

#pragma mark once
#include "ofMain.h"

#include "ofxAnimatableFloat.h"

class EffectController{
public:
    //vector <face> shaders;
    float targets[10];

    ofxAnimatableFloat fr, d;
    
    ofShader shader;
    
    EffectController();
    
    void loadShaders();
    
    void update();
    void draw(int offsetX, int offsetY, float time);
};
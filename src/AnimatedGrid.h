//
//  AnimatedGrid.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/19/13.
//
//

#pragma mark once
#include "ofMain.h"

#include "ofxAnimatableFloat.h"

class AnimatedGrid{
public:
    ofxAnimatableFloat alpha, gWidth, gHeight;
    ofShader grid;
    
    
    AnimatedGrid( int width, int height );
    
    void loadShaders();
    void update(int showState, float dt);
    void draw(float time, int offsetX, int height);
    
};
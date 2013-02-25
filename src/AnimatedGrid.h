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
    ofxAnimatableFloat alpha;
    ofShader grid;
    
    float timeScaler;
    
    AnimatedGrid( int width, int height );
    
    void loadShaders();
    void fadeOut();
    void fadeIn();
    void fadePartial(float newAlpha);
    void update(float dt);
    void draw(float time, int offsetX, int width, int height);
    
};
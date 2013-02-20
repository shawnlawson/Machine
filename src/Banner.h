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

class Banner{
public:
    float targets[10];

    ofxAnimatableFloat alpha;
    ofShader waves;


    Banner( int width, int height );
    
    void loadShaders();
    void update(int showState);
    void draw(float time, int offsetX, int height);
};
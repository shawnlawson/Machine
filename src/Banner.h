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
    ofxAnimatableFloat alpha;
    ofShader waves;

    float timeScaler;

    Banner( int width, int height );
    
    void loadShaders();
    void fadeOut();
    void fadeIn();
    void fadePartial(float newAlpha);
    void update(float dt);
    void draw(float time, int offsetX, int width, int height);
};
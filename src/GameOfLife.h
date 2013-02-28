//
//  GameOfLife.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/25/13.
//
//

#pragma once
#include "ofMain.h"

#include "ofxAnimatableFloat.h"


class GameOfLife{
    
public:
    ofFbo fbo;
    ofShader gol, colorNoise, bwNoise;
    ofxAnimatableFloat alpha;
    bool bFront;
    
    
    GameOfLife(int width, int height);
    
    void loadShader();
    void fadeOut();
    void fadeIn();
    void fadePartial(float newAlpha);
    void regenerate();
    void update(float dt);
    void draw(int x, int y);
};
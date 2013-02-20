//
//  AnimatedGrid.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 2/19/13.
//
//

#include "AnimatedGrid.h"

AnimatedGrid::AnimatedGrid( int width, int height )
{
    alpha.reset(1.0);

}

void AnimatedGrid::loadShaders()
{
    grid.load("shaders/gridy");
    gWidth.setRepeatType(LOOP_BACK_AND_FORTH);
    gWidth.animateFromTo(128.0, 512.0);
    gHeight.setRepeatType(LOOP_BACK_AND_FORTH);
    gHeight.animateFromTo(512.0, 128.0);
}


void AnimatedGrid::update(int showState, float dt )
{
    alpha.update(dt);
    gWidth.update(dt*.001);
    gHeight.update(dt*.001);
    
    switch (showState)
    {
            //all transparent now
        case 2:
            alpha.reset(0.0);
            break;
            
            //all opaque now
        case 3:
            alpha.reset(1.0);
            break;
            
            //random start fade in
        case 4:
            alpha.reset(0.0);
            alpha.animateToAfterDelay(1.0f, ofRandom(60.0));
            break;
            
            //random start fade out
        case 5:
            alpha.reset(1.0);
            alpha.animateToAfterDelay(0.0f, ofRandom(60.0));
            break;
            
            //gradually fade all transparent
        case 6:
            alpha.reset(1.0f);
            alpha.animateFromTo(1.0f, 0.0f);
            break;
            
            //gradually fade all opaque
        case 7:
            alpha.reset(0.0f);
            alpha.animateFromTo(0.0f, 1.0f);
            break;
            
        default:
            break;
    }
    
}

void AnimatedGrid::draw(float dt, int offsetX, int height)
{

    
    ofSetColor(128, 128, 128, alpha.val()*255);
    grid.begin();
    grid.setUniform2f("BrickPct", 0.05, 0.05);
    grid.setUniform2f("BrickSize", 15.0, 15.0);
    grid.setUniform2f("resolution", 512.0, 512.0);
    grid.setUniform2f("offset", offsetX/3640.0, 0.0);
    grid.setUniform1f("time", ofGetElapsedTimef()*.1);
    ofRect(offsetX, 0, 3640, height);
    grid.end();
}
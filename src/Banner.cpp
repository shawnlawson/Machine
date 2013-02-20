//
//  Banner.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 2/16/13.
//
//

#include "Banner.h"


Banner::Banner( int width, int height )
{
    targets[0] = 0.005;
    targets[1] = .013;
    targets[2] = .019;
    targets[3] = .026;
    targets[4] = .049;
    targets[5] = .058;
    targets[6] = .064;
    targets[7] = .068;
    targets[8] = .087;
    targets[9] = .091;
    
    alpha.reset(1.0);

}

void Banner::loadShaders()
{
    waves.load("shaders/waves");
}


void Banner::update(int showState)
{
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

void Banner::draw(float time, int offsetX, int height)
{
    ofSetColor(255, 255, 255, alpha.val()*255);
    waves.begin();
    waves.setUniform1f("time", time);
    waves.setUniform2f("mouse", 0.0, .7);
    waves.setUniform2f("resolution", 3640.0, height);
    waves.setUniform1f("offset", offsetX/3640.0);
    ofRect(offsetX, 0, 3640, height);
    waves.end();
}
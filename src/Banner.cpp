//
//  Banner.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 2/16/13.
//
//

#include "Banner.h"
#include "MyConstants.h"

Banner::Banner( int width, int height )
{
    alpha.reset(0.0);
    alpha.setDuration(60.0);
    timeScaler = 0.1;
}

void Banner::loadShaders()
{
    waves.load("shaders/waves");
}

void Banner::fadeOut()
{
    alpha.animateTo(0.0);
}

void Banner::fadeIn()
{
    alpha.animateTo(1.0);
}

void Banner::fadePartial(float newAlpha)
{
    alpha.animateTo(newAlpha);
}

void Banner::update(float dt)
{
    alpha.update(dt);
}

void Banner::draw(float time, int offsetX, int width, int height)
{
    waves.begin();
    waves.setUniform1f("time", time * timeScaler);
    waves.setUniform1f("alpha", alpha.val());
    waves.setUniform2f("mouse", 0.0, .6);
    waves.setUniform2f("resolution", width, height);
    waves.setUniform1f("offset", offsetX/width);
    ofRect(offsetX, 0, width, height);
    waves.end();
}
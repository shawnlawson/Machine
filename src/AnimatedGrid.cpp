//
//  AnimatedGrid.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 2/19/13.
//
//

#include "AnimatedGrid.h"
#include "MyConstants.h"

AnimatedGrid::AnimatedGrid( int width, int height )
{
    alpha.reset(1.0);
    timeScaler = 0.1;
}

void AnimatedGrid::loadShaders()
{
    grid.load("shaders/gridy");
}

void AnimatedGrid::fadeOut()
{
    alpha.animateTo(0.0);
}

void AnimatedGrid::fadeIn()
{
    alpha.animateTo(1.0);
}

void AnimatedGrid::fadePartial(float newAlpha)
{
    alpha.animateTo(newAlpha);
}

void AnimatedGrid::update(float dt )
{
    alpha.update(dt);
}

void AnimatedGrid::draw(float time, int offsetX, int width, int height)
{
    grid.begin();
    grid.setUniform1f("alpha", alpha.val());
    grid.setUniform2f("BrickPct", 0.05, 0.05);
    grid.setUniform2f("BrickSize", 15.0, 15.0);
    grid.setUniform2f("resolution", 512.0, 512.0);
    grid.setUniform2f("offset", offsetX/width, 0.0);
    grid.setUniform1f("time", time * timeScaler);
    ofRect(offsetX, 0, width, height);
    grid.end();
}
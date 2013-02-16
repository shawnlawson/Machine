//
//  EffectController.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 2/16/13.
//
//

#include "EffectController.h"


EffectController::EffectController()
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
    d.setDuration(6.0);
    d.setRepeatType(LOOP_BACK_AND_FORTH);
    d.animateFromTo(0.0, 10.0);
    fr.setDuration(3.0);
    fr.animateFromTo(0.0, targets[(int)ofRandom(9)]);
}

void EffectController::loadShaders()
{
    shader.load("shaders/banner");

}


void EffectController::update(){
    float dt  = ofGetLastFrameTime();
    d.update(dt);
    fr.update(dt);
    if(!fr.isOrWillBeAnimating()){
        fr.reset(fr.val());
        fr.animateToAfterDelay(targets[(int)ofRandom(9)], ofRandom(20.0, 25.0));
    }
}

void EffectController::draw(int offsetX, int offsetY, float time)
{
    shader.begin();
    shader.setUniform1f("dotSize", d.val());
    shader.setUniform1f("freq", fr.val());
    shader.setUniform1f("time", ofGetElapsedTimef()*0.1);
    shader.setUniform1f("height", 80.0);
    shader.setUniform2f("resolution", offsetX, offsetY);
    ofRect(offsetX, 0, 3640, 260);
    shader.end();
}
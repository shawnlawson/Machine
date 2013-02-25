//
//  GameOfLife.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 2/25/13.
//
//

#include "GameOfLife.h"



GameOfLife::GameOfLife(int width, int height){
    
    ofFbo::Settings s;
    s.width  = width;
    s.height = height;
    s.numColorbuffers = 2;
    fbo.allocate(s);
    
    alpha.reset(1.0);
    
    bFront = true;
}

void GameOfLife::loadShader(){
    gol.load("shaders/gol");
    colorNoise.load("shaders/colorNoise");
    
    fbo.begin();
    colorNoise.begin();
    ofRect(0, 0, fbo.getWidth(), fbo.getHeight());
    colorNoise.end();
    fbo.end();
}

void GameOfLife::fadeOut()
{
    alpha.animateTo(0.0);
}

void GameOfLife::fadeIn()
{
    alpha.animateTo(1.0);
}

void GameOfLife::fadePartial(float newAlpha)
{
    alpha.animateTo(newAlpha);
}

void GameOfLife::update(float dt){
    
    
}

void GameOfLife::draw(int x, int y){
    
    if(bFront)
    {    
        fbo.begin();
        gol.begin();
        glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT+1);
        gol.setUniformTexture("tex0", fbo.getTextureReference(), 0);
        fbo.getTextureReference(0).draw(0,0);
        gol.end();
        fbo.end();
    
        fbo.getTextureReference(1).draw(x,y);
    }
    else
    {
        fbo.begin();
        gol.begin();
        glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
        gol.setUniformTexture("tex0", fbo.getTextureReference(1), 0);
        fbo.getTextureReference(1).draw(0,0);
        gol.end();
        fbo.end();
        
        fbo.draw(x, y);
    }
    
    bFront = !bFront;
}


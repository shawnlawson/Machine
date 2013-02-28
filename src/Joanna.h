//
//  Joanna.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/27/13.
//
//

#pragma once
#include "ofMain.h"

#include "ofxAnimatableFloat.h"
#include "face.h"


class Joanna{

    public:
    face f;
    ofNode places[16];
    ofxAnimatableFloat alphas[16];
    float lineWidth;
    ofxAnimatableFloat whiteOut, vertexSize;
    ofShader fader;

    Joanna(){}
    
    void loadFaces(){
        whiteOut.reset(1.0);
        vertexSize.reset(2.0);
        lineWidth = 1.0;
        f = face();
        f.loadImage( "joanna.png" );
        f.loadMesh( "joanna.txt" );

        
        float posY = TILE_SIZE*4.0;
        
        for(int i=0;i<6;i++)
            places[i].setPosition((TILE_SIZE*3)+(i*TILE_SIZE*4), posY, 0.0f);
        for(int i=0;i<4;i++)
            places[i+6].setPosition((TILE_SIZE*26)+(TILE_SIZE*2)+(i*TILE_SIZE*5), posY, 0.0f);
        for(int i=0;i<6;i++)
            places[i+10].setPosition((TILE_SIZE*45)+(TILE_SIZE*3)+(i*TILE_SIZE*4), posY, 0.0f);
        for(int i=0;i<16;i++){
            places[i].setScale(1.5);
            places[i].rotate(ofRandom(100), 0, 1, 0);
            alphas[i].reset(0.0);
            alphas[i].setDuration(5.0);
        }
        
        fader.load("shaders/fader");
    }

    //--------------------------------------------------------------
    void setMode(ofPolyRenderMode newMode){
        f.drawMode = newMode;
    }

    //--------------------------------------------------------------
    void update(float dt){
//        f.update(dt);
        for(int i=0;i<16;i++){
            alphas[i].update(dt);
//            cout << alphas[i].val() << endl;
        }
        whiteOut.update(dt);
        vertexSize.update(dt);
    }
    
    //--------------------------------------------------------------
    void updateAlpha( int state, float delay ){
        
        switch (state) {
            case AllTransparentNow:
                for(int i=0; i<16; i++){
                    alphas[i].reset(0.0);
                }
                break;
                
            case AllOpaqueNow:
                for(int i=0; i<16; i++){
                    alphas[i].reset(1.0);
                }
                break;
                
            case RandomFadeIn:
                for(int i=0; i<16; i++){
                 //   alphas[i].reset(0.0);
                    alphas[i].animateToAfterDelay(1.0f, ofRandom(delay));
                }
                break;
                
            case RandomFadeOut:
                for(int i=0; i<16; i++){
                 //   alphas[i].reset(1.0f);
                    alphas[i].animateToAfterDelay(0.0f, ofRandom(delay));
                }
                break;
                
            case AllTransparentFade:
                for(int i=0; i<16; i++){
                    alphas[i].animateFromTo(1.0f, 0.0f);
                }
                break;
                
            case AllOpaqueFade:
                for(int i=0; i<16; i++){
                    alphas[i].animateFromTo(0.0f, 1.0f);
                }
                break;

                break;
            default:
                break;
        }

    }

    //--------------------------------------------------------------
    void draw(){
        glLineWidth(lineWidth);
        glPointSize(vertexSize.val());
 
        
        for (int i=0; i<16; i++) {
            places[i].rotate(.3, 0, 1, 0);
            places[i].transformGL();
            ofSetColor(255, 255, 255, alphas[i].val()*255.0);
            fader.begin();
            fader.setUniform1f("multiplier", whiteOut.val());
            fader.setUniformTexture("tex", f.image.getTextureReference(), 0);
 
            f.joannaDraw();
            fader.end();
            places[i].restoreTransformGL();
        }
        
        glLineWidth(1.0);
        glPointSize(1.0);
    }
};
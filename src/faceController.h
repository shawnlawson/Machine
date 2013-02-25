//
//  faceController.h
//  TheMachine
//
//  Created by Shawn Lawson on 1/26/13.
//
//

#pragma once
#include "ofMain.h"

#include "ofxAnimatableFloat.h"
#include "face.h"


class faceController{
    
public:
    vector <face> allFaces;
    face* facesOnScreen[NUM_PANELS];
    int faceToSwap;
    float vertexSize, lineWidth;
    ofxAnimatableFloat whiteOut;
    ofShader fader;

//--------------------------------------------------------------
    faceController(){}
    
//--------------------------------------------------------------
    void loadFaces( string path){
        whiteOut.reset(1.0);
        vertexSize = lineWidth = 1.0;
        faceToSwap = -1;
        ofDirectory dirImage, dirMesh;
        dirImage.allowExt("png");
        dirMesh.allowExt("txt");
        int numFaces = dirImage.listDir(path);
        int numMesh = dirMesh.listDir(path);
        if( numFaces == numMesh){
            for(int i=0; i<numMesh && i<40; i++){
                face f = face();
                f.loadImage( dirImage.getPath(i) );
                f.loadMesh( dirMesh.getPath(i) );
                f.setScale(.8);
                allFaces.push_back(f);
           }
        }
        
        resetFacesOnPanels();
        fader.load("shaders/fader");
    }
    
//--------------------------------------------------------------
    void updateShowState( int showState, float dt ){
        
        switch ( showState ) {

            case AllFacesDelete:
                resetFacesOnPanels();
                break;
                
            case AllFacesPopulate:
                resetFacesOnPanels();
                for( int i=0; i<NUM_PANELS; i++){
                    addFaceAtPlace(i, i);
                }
                break;
            
            case AllTransparentNow:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(0.0);
                }
                break;
            
            case AllOpaqueNow:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(255.0f);
                }
                break;
                
            case RandomFadeIn:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(0.0);
                    facesOnScreen[i]->alpha.animateToAfterDelay(255.0f, ofRandom(120.0));
                }
                break;
            
            case RandomFadeOut:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(255.0f);
                    facesOnScreen[i]->alpha.animateToAfterDelay(0.0f, ofRandom(120.0));
                }
                break;
                
            case AllTransparentFade:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.animateFromTo(255.0f, 0.0f);
                }
                break;
                
            case AllOpaqueFade:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.animateFromTo(0.0f, 255.0f);
                }
                break;
                
            case SwapFaces:
                if(faceToSwap < 0)
                    startFaceSwap();
                else
                    waitForSwap();
                
                break;
            default:
                break;
        }
        
        for(int i=0; i<NUM_PANELS; i++){
            facesOnScreen[i]->update(dt);
        }
        
        whiteOut.update(dt);
        
    }

//--------------------------------------------------------------  
    void setMode(ofPolyRenderMode newMode){
        for (int i=0; i<allFaces.size(); i++) {
            allFaces[i].drawMode  = newMode;
        }
    }
    
//--------------------------------------------------------------
    void draw(){
        glLineWidth(lineWidth);
        glPointSize(vertexSize);
        fader.begin();        
        for (int i=0; i<NUM_PANELS; i++) {
            fader.setUniform1f("multiplier", whiteOut.val());
            fader.setUniformTexture("tex", facesOnScreen[i]->image.getTextureReference(), 0);
            facesOnScreen[i]->customDraw();
        }
        fader.end();
        glLineWidth(1.0);
        glPointSize(1.0);
    }

private:
//--------------------------------------------------------------
    void resetFacesOnPanels(){
        
        for(int i=0; i<NUM_PANELS; i++)
            facesOnScreen[i] = NULL;
        
        for(int i=0; i<allFaces.size(); i++) {
            allFaces[i].alpha.reset(0.0);
            allFaces[i].inUse = false;
        }  
    }

//--------------------------------------------------------------
    void waitForSwap(){
        
        if( !facesOnScreen[faceToSwap]->alpha.isOrWillBeAnimating() ){
            
            int testSwap = (int)ofRandom(allFaces.size()-1);
            
            if( !allFaces[testSwap].inUse ){
                facesOnScreen[faceToSwap]->inUse = false;
                addFaceAtPlace(faceToSwap, testSwap);
                facesOnScreen[faceToSwap]->alpha.reset(0.0);
                facesOnScreen[faceToSwap]->alpha.animateFromTo(0.0f, 255.0f);
                faceToSwap = -1;
            }
        }
        
    }
    
//--------------------------------------------------------------
    void startFaceSwap(){
        
        int possibleSwap = (int)ofRandom(NUM_PANELS);
        
        if( !facesOnScreen[possibleSwap]->alpha.isOrWillBeAnimating() ){
            faceToSwap = possibleSwap;
            facesOnScreen[faceToSwap]->alpha.reset(255.0f);
            facesOnScreen[faceToSwap]->alpha.animateFromTo(255.0f, 0.0f);
        }
    }
    
//--------------------------------------------------------------    
    void addFaceAtPlace(int place, int faceToUse){
        
        float posY, posX;
        
        if(place<35)    //top half
            posY = TILE_SIZE*3.0;
        else        //bottom half
            posY = TILE_SIZE*5.0;
        
        int tempX = place%35;
        
        if( tempX < 18 ) //east wall left
            posX = TILE_SIZE + tempX*TILE_SIZE*2;
        else if( tempX < 22) //east wall right
            posX = TILE_SIZE + TILE_SIZE + tempX*TILE_SIZE*2;
        else //south wall
            posX = TILE_SIZE/2 +TILE_SIZE + TILE_SIZE + tempX*TILE_SIZE*2;
        
        facesOnScreen[place] = &allFaces[faceToUse];
        facesOnScreen[place]->setPosition(posX, posY, 0.0f);
        facesOnScreen[place]->inUse = true;
    }
};
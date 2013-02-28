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
    int faceToSwap, loaded, totalToLoad;
    float lineWidth;
    ofxAnimatableFloat whiteOut, vertexSize;
    ofShader fader;
    
    bool swapFaces;

//--------------------------------------------------------------
    faceController(){
        loaded = 0;
        totalToLoad = 0;
    }
    
//--------------------------------------------------------------
    void loadFaces( string path){
        whiteOut.reset(1.0);
        vertexSize.reset(1.0);
        lineWidth = 1.0;
        faceToSwap = -1;
        ofDirectory dirImage, dirMesh;
        dirImage.allowExt("png");
        dirMesh.allowExt("txt");
        int numFaces = dirImage.listDir(path);
        int numMesh = dirMesh.listDir(path);
        totalToLoad = numMesh;
        if( numFaces == numMesh){
            for(int i=0; i<numMesh && i< NUM_PANELS; i++){
                face f = face();
                f.loadImage( dirImage.getPath(i) );
                f.loadMesh( dirMesh.getPath(i) );
                f.setScale(.5);
                allFaces.push_back(f);
                loaded = i;
                cout << "loaded: " << loaded << endl;
           }
        }
        
        resetFacesOnPanels();
        for( int i=0; i<NUM_PANELS; i++){
            addFaceAtPlace(i, i);
        }
        fader.load("shaders/fader");
        swapFaces = true;
    }
    
//--------------------------------------------------------------
    void updateShowState( int showState, float timeDelay ){
        
        if(loaded == 0)
            return;
        
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
                    facesOnScreen[i]->alpha.animateToAfterDelay(255.0f, ofRandom(timeDelay));
                }
                break;
            
            case RandomFadeOut:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(255.0f);
                    facesOnScreen[i]->alpha.animateToAfterDelay(0.0f, ofRandom(15.0));
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
                
            default:
                break;

        }
 }
    
void update( float dt ){
    if( SwapFaces ){
        if(faceToSwap < 0)
            startFaceSwap();
        else
            waitForSwap();
    }
    
    for(int i=0; i<NUM_PANELS; i++){
        facesOnScreen[i]->update(dt);
    }
    
    whiteOut.update(dt);
    vertexSize.update(dt);
        
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
        glPointSize(vertexSize.val());
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
        
        if(allFaces.size()==0)
            return;
        
        int possibleSwap = (int)ofRandom(NUM_PANELS);
        
        if( !facesOnScreen[possibleSwap]->alpha.isOrWillBeAnimating() ){
            faceToSwap = possibleSwap;
            facesOnScreen[faceToSwap]->alpha.reset(255.0f);
            facesOnScreen[faceToSwap]->alpha.animateFromTo(255.0f, 0.0f);
            cout << faceToSwap << endl;
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
            posX = TILE_SIZE + TILE_SIZE + tempX*TILE_SIZE*2;
        
        facesOnScreen[place] = &allFaces[faceToUse];
        facesOnScreen[place]->setPosition(posX, posY, 0.0f);
        facesOnScreen[place]->inUse = true;
    }
};
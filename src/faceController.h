//
//  faceController.h
//  TheMachine
//
//  Created by Shawn Lawson on 1/26/13.
//
//

#pragma mark once
#include "ofMain.h"

#include "face.h"

#define NUM_PANELS 20 //72

class faceController{
    
public:
    vector <face> allFaces;
    face* facesOnScreen[NUM_PANELS] = {NULL};
    int faceToSwap = -1;

//--------------------------------------------------------------
    faceController(){}
    
//--------------------------------------------------------------
    void loadFaces( string path){
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
    }
    
//--------------------------------------------------------------
    void updateShowState( int showState ){
        
        switch ( showState ) {
            //delete everything
            case 0:
                resetFacesOnPanels();
                break;
                
            //populate everything
            case 1:
                resetFacesOnPanels();
                for( int i=0; i<NUM_PANELS; i++){
                    addFaceAtPlace(i, i);
                }
                break;
            
            //set all to transparent now
            case 2:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(0.0);
                }
                break;
            
            //set all opaque now
            case 3:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(1.0f);
                }
                break;
                
            //random start fade in
            case 4:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(0.0);
                    facesOnScreen[i]->alpha.animateToAfterDelay(1.0f, ofRandom(60.0));
                }
                break;
            
            //random start fade out
            case 5:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.reset(1.0);
                    facesOnScreen[i]->alpha.animateToAfterDelay(0.0f, ofRandom(60.0));
                }
                break;
                
            //gradually fade all to transparent
            case 6:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.animateFromTo(1.0f, 0.0f);
                }
                break;
                
            //gradually fade all to opaque
            case 7:
                for(int i=0; i<NUM_PANELS; i++){
                    facesOnScreen[i]->alpha.animateFromTo(0.0f, 1.0f);
                }
                break;
                
            //swap faces
            case 8:
                if(faceToSwap < 0)
                    startFaceSwap();
                else
                    waitForSwap();
                
                break;
            default:
                break;
        }
    }

    
    void draw(){
        
        for (int i=0; i<NUM_PANELS; i++) {
            facesOnScreen[i]->customDraw();
        }

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
                facesOnScreen[faceToSwap]->alpha.animateFromTo(0.0f, 1.0f);
                faceToSwap = -1;
            }
        }
        
    }
    
//--------------------------------------------------------------
    void startFaceSwap(){
        
        int possibleSwap = (int)ofRandom(NUM_PANELS);
        
        if( !facesOnScreen[possibleSwap]->alpha.isOrWillBeAnimating() ){
            faceToSwap = possibleSwap;
            facesOnScreen[faceToSwap]->alpha.reset(1.0f);
            facesOnScreen[faceToSwap]->alpha.animateFromTo(1.0f, 0.0f);
        }
    }
    
//--------------------------------------------------------------    
    void addFaceAtPlace(int place, int faceToUse){
        
        float posY, posX;
        int fPanel = 130.0; //change when we know
        int hPanel = 130.0; //change when we know
        
        if(place<36)    //top half
            posY = 390.0f;
        else        //bottom half
            posY = 650.0f;
        
        int tempX = place%36;
        
        if( tempX < 13 ) // north wall
            posX = hPanel+fPanel + tempX*fPanel*2;
        else if( tempX < 18 ) //east wall left
            posX = hPanel+fPanel + hPanel*2 + tempX*fPanel*2;
        else if( tempX < 23)
            posX = hPanel+fPanel + hPanel*2 + fPanel + tempX*fPanel*2;
        else
            posX = hPanel+fPanel + hPanel*2 + fPanel + hPanel*2 + tempX*fPanel*2;
        
        facesOnScreen[place] = &allFaces[faceToUse];
        facesOnScreen[place]->setPosition(posX, posY, 0.0f);
        facesOnScreen[place]->inUse = true;
    }
};
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

#define NUM_PANELS 72

class faceController{
    
public:
    vector <face> allFaces;
    vector <face*> facesOnScreen;
    vector  <int> slotsEmpty;

//--------------------------------------------------------------
    faceController(){
        for(int i=0; i<NUM_PANELS; i++)
            slotsEmpty.push_back(i);
    }
    
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
                if(facesOnScreen.size() != NUM_PANELS){
                    resetFacesOnPanels();
                    for( int i=0; i<NUM_PANELS; i++){
                        slotsEmpty.erase( remove(slotsEmpty.begin(), slotsEmpty.end(), i) );
                        addFaceAtPlace(i, i);
                    }
                }
                break;
            
            //set all to transparent now
            case 2:
                for(int i=0; i<facesOnScreen.size(); i++){
                    facesOnScreen[i]->alpha.reset(1.0);
                }
                break;
            
            //set all opaque now
            case 3:
                for(int i=0; i<facesOnScreen.size(); i++){
                    facesOnScreen[i]->alpha.reset(0.0);
                }
                break;
                
            //gradually add and fade in
            case 4:
                if( facesOnScreen.size()<NUM_PANELS ){
                    addFaceToPanel();
                }else{
                    
                    
                }
                break;
            
            //gradually fade out and delete
            case 5:
                
                break;
                
            default:
                break;
        }
    }

    
    void draw(){
        
        for (int i=0; i<facesOnScreen.size(); i++) {
            facesOnScreen[i]->customDraw();
        }

    }

private:
//--------------------------------------------------------------    
    void resetFacesOnPanels(){
        facesOnScreen.clear();
        slotsEmpty.clear();
        
        for(int i=0; i<NUM_PANELS; i++)
            slotsEmpty.push_back(i);
        
        for(int i=0; i<allFaces.size(); i++) {
            allFaces[i].alpha.reset(0.0);
            allFaces[i].inUse = false;
        }  
    }
    
//--------------------------------------------------------------    
    void addFaceToPanel(){

        int whichFaceToUse = (int)ofRandom(allFaces.size()-1);

        if (!allFaces[whichFaceToUse].inUse) {

            int place = (int)ofRandom(NUM_PANELS);
            
            vector<int>::iterator it;
            it = find(slotsEmpty.begin(), slotsEmpty.end(), place);
            
            if(*it == place){
                slotsEmpty.erase( remove(slotsEmpty.begin(), slotsEmpty.end(), place) );
                addFaceAtPlace(place, whichFaceToUse);
                allFaces[whichFaceToUse].inUse = true;
            }else{
            
            }
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
        
        facesOnScreen.push_back( &allFaces[faceToUse] );
        face* f = facesOnScreen[facesOnScreen.size()-1];
        f->setPosition(posX, posY, 0.0f);
    }
};
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



class faceController{
    
public:
    
    vector <face> faces;
    
    faceController(){
        
    }
    
    ~faceController(){

    }
    
    void loadFaces( string path){
        ofDirectory dir;
        dir.allowExt("png");
        int numFaces   = dir.listDir(path);
        for(int i=0; i<numFaces; i++){
            face f = face();
            f.loadImage( dir.getPath(i) );
            f.position = ofVec2f( 130* i, 0);
            faces.push_back(f);
        }

    }
    
void update(){}

    
void draw(){
    
    for(vector<face>::iterator it =  faces.begin(); it != faces.end(); ++it){
        it->draw();
    }

}

};
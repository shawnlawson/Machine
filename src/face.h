//
//  face.h
//  TheMachine
//
//  Created by Shawn Lawson on 1/26/13.
//
//

#pragma mark once
#include "ofMain.h"

class face{

    
public:
    ofVec2f position;
    
    ofImage image;
    
    face(){}
    
    void loadImage( string path){
        image.allocate(130, 130, OF_IMAGE_COLOR);
        image.loadImage(path);
    }
    
    void update(){}
    
    void draw(){
        image.draw(position);
    }
    
};
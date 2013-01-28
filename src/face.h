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
    ofVboMesh vboMesh;
    
    face(){}
    
    //--------------------------------------------------------------
    void loadImage( string path ){
        image.allocate(130, 130, OF_IMAGE_COLOR_ALPHA);
        image.loadImage(path);
    }
    
    //--------------------------------------------------------------
    void loadMesh( string path ){
        
        ofFile file(path);
        
        if(!file.exists()){
            ofLogError( "z data file not found: "+path);
        }
        
        ofBuffer buffer(file);
        vector<float> zData;
        
        while (!buffer.isLastLine()) {
            string line = buffer.getNextLine();
            //Split line into strings
//            vector<string> words = ofSplitString(line, ",");
//            symbol.character = words[0];
//            symbol.code = words[1];
            
            //ofMap to push data front to back around pivot point
            //might need to be -65 65 to match tile size of 130
            zData.push_back( ofMap(ofToFloat(line), 100, 255, -65, 65) );
        }

       // vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        vboMesh.setMode(OF_PRIMITIVE_POINTS);
        int skip = 1;	// this controls the resolution of the mesh
        int width = image.getWidth();
        int height = image.getHeight();
        ofVec3f zero(0, 0, 0);
        for(int y = 0; y < height - skip; y += skip) {
            for(int x = 0; x < width - skip; x += skip) {

                ofVec3f nw = ofVec3f(x, y, zData[y*width + x]);
                ofVec3f ne = ofVec3f(x + skip, y, zData[y*width + x+1]);
                ofVec3f sw = ofVec3f(x, y + skip, zData[(y+1)*width + x]);
                ofVec3f se = ofVec3f(x + skip, y + skip, zData[(y+1)*width + x+1]);
                ofVec2f nwi(x, y);
                ofVec2f nei(x + skip, y);
                ofVec2f swi(x, y + skip);
                ofVec2f sei(x + skip, y + skip);
                
                addFace(nw, ne, se, sw);
                addTexCoords(nwi, nei, sei, swi);
                
                
                if( zData[y*width +x]< -65.0){
                    image.setColor(x, y, ofColor(1, 1, 1, 0));
                }
            }
        }


        
    }
    
    //--------------------------------------------------------------
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c) {
        vboMesh.addVertex(a);
        vboMesh.addVertex(b);
        vboMesh.addVertex(c);
    }
    
    //--------------------------------------------------------------
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
        addFace(a, b, c);
        addFace(a, c, d);
    }
    
    //--------------------------------------------------------------
    void addTexCoords(ofVec2f a, ofVec2f b, ofVec2f c) {
        vboMesh.addTexCoord(a);
        vboMesh.addTexCoord(b);
        vboMesh.addTexCoord(c);
    }
    
    //--------------------------------------------------------------
    void addTexCoords(ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d) {
        addTexCoords(a, b, c);
        addTexCoords(a, c, d);
    }
    
    //--------------------------------------------------------------
    void update(){}

    //--------------------------------------------------------------
    void draw(){
        //just image
  //      image.draw(position);
        
     //   ofScale(1, -1, 1); // make y point down
     //   ofScale(.5, .5, .5); // make everything a bit smaller
       
        //point cloud
        image.bind();
        ofPushMatrix();
            ofTranslate(position);
            ofPushMatrix();
                ofTranslate(65, 65);
                ofRotate(ofGetElapsedTimef()*20, 0, 1, 0);
                ofTranslate(-65, -65);
                vboMesh.draw();
            ofPopMatrix();
        ofPopMatrix();
        image.unbind();
        
    }
    
};
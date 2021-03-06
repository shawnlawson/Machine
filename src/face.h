//
//  face.h
//  TheMachine
//
//  Created by Shawn Lawson on 1/26/13.
//
//

#pragma once
#include "ofMain.h"

#define toClose 50
#define toFar   1000

class face : public ofNode, ofVboMesh{

public:
    ofImage image;
    ofxAnimatableFloat alpha;
    bool inUse;
    ofPolyRenderMode drawMode;
    
    face(){
        inUse = false;
        alpha.reset(0.0);
        alpha.setDuration(5.0);
        drawMode = OF_MESH_FILL;
    }
    
    //--------------------------------------------------------------
    void loadImage( string path ){
        image.allocate(300, 300, OF_IMAGE_COLOR_ALPHA);
        image.loadImage(path);
        image.setAnchorPercent(0.5, 0.5);
    }
    
    //--------------------------------------------------------------
    void loadMesh( string path ){
        
        ofFile file(path);
        
        if(!file.exists()){
            ofLogError( "file not found: "+path);
        }
        
        ofBuffer buffer(file);
        vector<ofVec3f> vData;

        int skip = 4;	// this controls the resolution of the mesh
        int width = image.getWidth();
        int height = image.getHeight();
        ofVec3f zero(0, 0, 0);
        while (!buffer.isLastLine()) {
            string line = buffer.getNextLine();
            vector<string> vert = ofSplitString(line, " ");
            vData.push_back(ofVec3f(ofToFloat(vert[0]), ofToFloat(vert[1]), ofToFloat(vert[2])));
        }
        
        for(int y = 0; y < height - skip; y += skip) {
            for(int x = 0; x < width - skip; x += skip) {
                
                ofVec3f nw = vData[y*width + x];
                ofVec3f ne = vData[y*width + x+skip];
                ofVec3f sw = vData[(y+skip)*width + x];
                ofVec3f se = vData[(y+skip)*width + x+skip];
                
                if(nw.z > toClose && nw.z < toFar &&
                   ne.z > toClose && ne.z < toFar &&
                   sw.z > toClose && sw.z < toFar &&
                   se.z > toClose && se.z < toFar ){
                    
                    addFace(nw, ne, se, sw);
                    
                    ofVec2f nwi(x, y);
                    ofVec2f nei(x + skip, y);
                    ofVec2f swi(x, y + skip);
                    ofVec2f sei(x + skip, y + skip);
                    addTexCoords(nwi, nei, sei, swi);
                }
            }
        }
        
        ofVec3f center = getCentroid();
        ofVec3f *v = getVerticesPointer();
        
        for(int i=0; i<getNumVertices(); i++){
            v->x -= center.x;
            v->y -= center.y;
            v->z -= center.z;
            v++;
        }

        enableColors();
        rotate(ofRandom(100), 0, 1, 0);
    }
    
    //--------------------------------------------------------------
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c) {
        addVertex(a);
        addVertex(b);
        addVertex(c);
    }
    
    //--------------------------------------------------------------
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
        addFace(a, b, c);
        addFace(a, c, d);
    }
    
    //--------------------------------------------------------------
    void addTexCoords(ofVec2f a, ofVec2f b, ofVec2f c) {
        addTexCoord(a);
        addTexCoord(b);
        addTexCoord(c);
    }
    
    //--------------------------------------------------------------
    void addTexCoords(ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d) {
        addTexCoords(a, b, c);
        addTexCoords(a, c, d);
    }
    
    //--------------------------------------------------------------
    void update(float dt ){
        alpha.update(dt);
    }

    //--------------------------------------------------------------
    void customDraw(){
       // image.draw(getPosition());
        
        ofSetColor(255, 255, 255, alpha.val());

      //  image.bind();
        
        rotate(.4, 0, 1, 0);
        transformGL();
      if( drawMode == OF_MESH_FILL)  drawFaces();
      else if( drawMode == OF_MESH_WIREFRAME) drawWireframe();
      else if( drawMode == OF_MESH_POINTS) drawVertices();
        restoreTransformGL();

   //     image.unbind();
   
    }
    void joannaDraw(){

        if( drawMode == OF_MESH_FILL)  drawFaces();
        else if( drawMode == OF_MESH_WIREFRAME) drawWireframe();
        else if( drawMode == OF_MESH_POINTS) drawVertices();
    }
};
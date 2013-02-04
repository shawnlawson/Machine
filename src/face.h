//
//  face.h
//  TheMachine
//
//  Created by Shawn Lawson on 1/26/13.
//
//

#pragma mark once
#include "ofMain.h"

class face : public ofNode, ofVboMesh{

public:
    ofImage image;
    
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
            ofLogError( "file not found: "+path);
        }
        
        ofBuffer buffer(file);
        vector<float> data;

        ofPixels pixels;
        pixels.allocate(130, 130, OF_PIXELS_RGBA);
        image.allocate(130, 130, OF_IMAGE_COLOR_ALPHA);
        
        enableColors();

        
        int pos = 0;
        
        while (!buffer.isLastLine()) {
            string line = buffer.getNextLine();
            vector<string> colors = ofSplitString(line, " ");
            
            //pixels.setColor(pos%130, (int)((pos-(pos%130))/130), ofColor(ofToFloat(colors[0]), ofToFloat(colors[1]), ofToFloat(colors[2])));
           // cout << line << endl;
            //safety check
            if(!buffer.isLastLine()){
                string line2 = buffer.getNextLine();
                vector<string> vert = ofSplitString(line2, " ");
//                data.push_back(ofToFloat(vert[0]));
//                data.push_back(ofToFloat(vert[1]));
//                data.push_back(ofToFloat(vert[2]));
                if( vert.size() == 3){
                    if( ofToFloat(vert[2]) < 1000  && ofToFloat(vert[2]) > 400){
                        addVertex(ofVec3f(ofToFloat(vert[0])-17, ofToFloat(vert[1])+70, ofToFloat(vert[2])-800));
                        if( colors.size() == 3){
                            addColor(ofFloatColor(ofToFloat(colors[0]), ofToFloat(colors[1]), ofToFloat(colors[2])));
                        }else{
                            cout << "color burp " << pos << endl;
                        }
                    }
                }else{
                    cout << "vert burp " << pos << endl;
                }            
                
                
                pos++;
            }
            
            pos++;
        }

        setPosition(130, 130, 0);
               
//        image.setFromPixels(pixels);
        
//        while (!buffer.isLastLine()) {
//            string line = buffer.getNextLine();
//            
//            float zTemp = ofClamp(ofToFloat(line), 127, 255);
//            data.push_back( ofMap(zTemp, 127.0, 255.0, 0.0, -130.0) );
//        }
//
//        int skip = 2;//1;	// this controls the resolution of the mesh
//        int width = image.getWidth();
//        int height = image.getHeight();
//        ofVec3f zero(0, 0, 0);
//        for(int y = 0; y < height - skip; y += skip) {
//            for(int x = 0; x < width - skip; x += skip) {
//
//                //think about checking alpha of image and then not adding mesh for those parts
//                //depth buffer & alpha blend issues... 
//                
//                ofVec3f nw = ofVec3f(x, y, data[y*width + x]);
//                ofVec3f ne = ofVec3f(x + skip, y, data[y*width + x+1]);
//                ofVec3f sw = ofVec3f(x, y + skip, data[(y+1)*width + x]);
//                ofVec3f se = ofVec3f(x + skip, y + skip, data[(y+1)*width + x+1]);
//                ofVec2f nwi(x, y);
//                ofVec2f nei(x + skip, y);
//                ofVec2f swi(x, y + skip);
//                ofVec2f sei(x + skip, y + skip);
//                
//                addFace(nw, ne, se, sw);
//                addTexCoords(nwi, nei, sei, swi);
//                
//            }
//        }
//

        
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
    void update(){
    
    }

    //--------------------------------------------------------------
    void customDraw(){
        //just image
     //   image.draw(position);


     //   image.bind();

        rotate(1, 0, 1, 0);
        transformGL();
        drawVertices();
        restoreTransformGL();

    //    image.unbind();
     

        
    }
    
};
//
//  MachineMapping2D.h
//  TheMachine
//
//  Created by Shawn Lawson on 1/28/13.
//
//

#pragma once
// OF
#include "ofMain.h"

// Addons
#include "ofxXmlSettings.h"

//Mapping
#include "ofxMtlMapping2DVertex.h"
#include "ofxMtlMapping2DQuad.h"
#include "ofxMtlMapping2DTriangle.h"
#include "ofxMtlMapping2DMask.h"
#include "ofxMtlMapping2DShape.h"

#include "mtlUtils.h"


//========================================================================
class MachineMapping2D {
public:
    MachineMapping2D();
    virtual ~MachineMapping2D();
    void init(int width, int height, string mappingXmlFilePath = "mapping/xml/shapes.xml");
    void update();
    
    void bind();
    void unbind();
    void drawFbo();
    void draw();
     
    ofFbo _fbo;
private:

    string _mappingXmlFilePath;
    
    ofxXmlSettings _shapesListXML;
//    list<ofxMtlMapping2DShape*>::iterator iteratorForShapeWithId(int shapeId);
    list<ofxMtlMapping2DShape*> pmShapes;
    
    void render();
    
    void loadShapesList();

};
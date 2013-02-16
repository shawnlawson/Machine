//
//  MachineMapping2D.cpp
//  TheMachine
//
//  Created by Shawn Lawson on 1/28/13.
//
//

#include "MachineMapping2D.h"
#include "ofxMtlMapping2DSettings.h"
#include "ofxMtlMapping2DInput.h"
#include "ofxMtlMapping2DShapeType.h"


//--------------------------------------------------------------
//--------------------------------------------------------------
MachineMapping2D::MachineMapping2D()
{
}

//--------------------------------------------------------------
MachineMapping2D::~MachineMapping2D()
{
    // ----
    while(!pmShapes.empty()) delete pmShapes.back(), pmShapes.pop_back();
	pmShapes.clear();
}

//--------------------------------------------------------------
void MachineMapping2D::init(int width, int height, string mappingXmlFilePath)
{
    _fbo.allocate(width, height, GL_RGBA);

    // ----
    _mappingXmlFilePath = mappingXmlFilePath;
    
    loadShapesList();
}

//--------------------------------------------------------------
void MachineMapping2D::update()
{
  
}

#pragma mark -
#pragma mark Draw / Edit Mode
//--------------------------------------------------------------
void MachineMapping2D::draw()
{
    render();
}

#pragma mark -
#pragma mark FBO
//--------------------------------------------------------------
void MachineMapping2D::bind()
{
    _fbo.bind();
  //  ofSetColor(0, 0, 0, 255);
  //  ofRect(0, 0, _fbo.getWidth(), _fbo.getHeight());
//    ofClear(0.0f, 0.0f, 0.0f, 1.0f);
    //ofClear(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    //ofClearAlpha();
}

//--------------------------------------------------------------
void MachineMapping2D::unbind()
{
    _fbo.unbind();
}

//--------------------------------------------------------------
void MachineMapping2D::drawFbo()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    _fbo.draw(0, 0);
}

#pragma mark -
#pragma mark Render - Mapping Mode
//--------------------------------------------------------------
void MachineMapping2D::render()
{
    list<ofxMtlMapping2DShape*>::iterator it;
    
    // Textured shapes
    _fbo.getTextureReference().bind();
    ofSetColor(255, 255, 255, 255);
    for (it=pmShapes.begin(); it!=pmShapes.end(); it++) {
        ofxMtlMapping2DShape* shape = *it;
        
        if (shape->shapeType != MAPPING_2D_SHAPE_MASK) {
            shape->render();
        }
    }
    _fbo.getTextureReference().unbind();
}


#pragma mark -
#pragma mark Load and Save Shapes List
//--------------------------------------------------------------
void MachineMapping2D::loadShapesList()
{
    
    // Delete everything
    while(!pmShapes.empty()) delete pmShapes.back(), pmShapes.pop_back();
    pmShapes.clear();

    
    
    //LOAD XML
    // ----
	//the string is printed at the top of the app
	//to give the user some feedback
	string feedBackMessage = "loading " + _mappingXmlFilePath;
	ofLog(OF_LOG_NOTICE, "Status > " + feedBackMessage);
    
	//we load our settings file
	//if it doesn't exist we can still make one
	//by hitting the 's' key
	if( _shapesListXML.loadFile(_mappingXmlFilePath) ){
		feedBackMessage = _mappingXmlFilePath + " loaded!";
	}else{
		feedBackMessage = "unable to load " + _mappingXmlFilePath + " check data/ folder";
	}
    ofLog(OF_LOG_NOTICE, "Status > " + feedBackMessage);
    
    
    int shapeId = -1;
    
    // ----
	//this is a more advanced use of ofXMLSettings
	//we are going to be reading multiple tags with the same name
	
	//lets see how many <root> </root> tags there are in the xml file
	int numRootTags = _shapesListXML.getNumTags("root");
	int numShapeTags = 0;
	
	//if there is at least one <root> tag we can read the list of cards
	//and then load their associated xml file
	if(numRootTags > 0){
		//we push into the last <root> tag
		//this temporarirly treats the tag as
		//the document root.
		_shapesListXML.pushTag("root", 0);
		
		//we see how many params/items we have stored in <card> tags
		numShapeTags = _shapesListXML.getNumTags("shape");
        ofLog(OF_LOG_NOTICE, "Status > numShapeTags :: " + ofToString(numShapeTags));
		
		if(numShapeTags > 0){
			for(int i = 0; i < numShapeTags; i++){
				ofxMtlMapping2DShape* newShape;
				
				shapeId = _shapesListXML.getAttribute("shape", "id", 0, i);
				
				_shapesListXML.pushTag("shape", i);
				
                //SHAPES SETTINGS
                int numShapeSettingTags = _shapesListXML.getNumTags("setting");
                
                string shapeType = _shapesListXML.getValue("setting", "nan", 0);
                
                if (shapeType == "quad") {
                    newShape = new ofxMtlMapping2DQuad();
                    newShape->shapeType = MAPPING_2D_SHAPE_QUAD;
                } else if (shapeType == "triangle") {
                    newShape = new ofxMtlMapping2DTriangle();
                    newShape->shapeType = MAPPING_2D_SHAPE_TRIANGLE;
                } else if (shapeType == "mask") {
                    newShape = new ofxMtlMapping2DMask();
                    newShape->shapeType = MAPPING_2D_SHAPE_MASK;
                } else {
                    newShape = new ofxMtlMapping2DQuad();
                    newShape->shapeType = MAPPING_2D_SHAPE_QUAD;
                }
                
                if(numShapeSettingTags > 0) {
                    for(int j = 0; j < numShapeSettingTags; j++){
                        string key = _shapesListXML.getAttribute("setting", "key", "nc", j);
                        string value = _shapesListXML.getValue("setting", "", j);
                        newShape->shapeSettings[key] = value;
                    }
                }
				
                //OUTPUT VERTICES
                _shapesListXML.pushTag("outputVertices", 0);
                int numVertexItemTags = _shapesListXML.getNumTags("vertex");
                for (int j = 0; j < numVertexItemTags; j++) {
                    int x = _shapesListXML.getAttribute("vertex", "x", 0, j);
                    int y = _shapesListXML.getAttribute("vertex", "y", 0, j);
                    
                    //Create a new vertex
                    ofxMtlMapping2DVertex* newVertex = new ofxMtlMapping2DVertex();
                    newVertex->init(x-newVertex->width/2, y-newVertex->height/2);
                    newShape->vertices.push_back(newVertex);
                }
                _shapesListXML.popTag();
                
                
                if(newShape->shapeType != MAPPING_2D_SHAPE_MASK) {
                    //INPUT QUADS
                    _shapesListXML.pushTag("inputPolygon", 0);
                    
                    //Create a new vertex
                    newShape->inputPolygon = new ofxMtlMapping2DInput();
                    
                    //INPUT VERTICES
                    numVertexItemTags = _shapesListXML.getNumTags("vertex");
                    for (int k = 0; k < numVertexItemTags; k++) {
                        int x = _shapesListXML.getAttribute("vertex", "x", 0, k);
                        int y = _shapesListXML.getAttribute("vertex", "y", 0, k);
                        
                        //Create a new vertex
                        ofxMtlMapping2DVertex* newVertex = new ofxMtlMapping2DVertex();
                        newVertex->init(x-newVertex->width/2, y-newVertex->height/2);
                        newVertex->isDefiningTectureCoord = true;
                        newShape->inputPolygon->vertices.push_back(newVertex);
                    }
                    
                    newShape->inputPolygon->init(shapeId);
                    _shapesListXML.popTag();
                }
                
                newShape->init(shapeId);
                pmShapes.push_front(newShape);
                
				_shapesListXML.popTag();
				
			}
		}
		
		//this pops us out of the <root> tag
		//sets the root back to the xml document
		_shapesListXML.popTag();
	}
    
  //  ofxMtlMapping2DShape::nextShapeId = shapeId;
}

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
   //   ofSetLogLevel(OF_LOG_VERBOSE);
    
    
    myImg.loadImage("someLargeImage.jpg");
        myImg2.loadImage("river.jpg");
    
    test = 1.0;
    
    northMapping = new ofxMtlMapping2D();
    northMapping->init(3640, 780, "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");

    southMapping = new ofxMtlMapping2D();
    southMapping->init(3640, 780, "mapping/xml/shapes2.xml", "mapping/controls/mapping2.xml");
    
    eastMapping = new ofxMtlMapping2D();
    eastMapping->init(3640, 780, "mapping/xml/shapes2.xml", "mapping/controls/mapping3.xml");
   
}

//--------------------------------------------------------------
void testApp::update(){

    northMapping->update();
    southMapping->update();
    eastMapping->update();

    northMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false);
    ofSetColor(255);
    myImg.draw(0,0);
    ofPopView();
    northMapping->unbind();

    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false);
    ofSetColor(255);
    myImg2.draw(0,0);
    ofPopView();
    southMapping->unbind();
    
    eastMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false);
    ofSetColor(255);

    ofPopView();
    eastMapping->unbind();
    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofPushMatrix();
    
    ofScale( .25, .25);

        ofSetColor(255);
        ofBackground(0, 0, 0);
        
        ofSetColor(128, 0, 0);
        ofRect(0, 0, 1920, 1080);
        ofSetColor(0, 128, 0);
        ofRect(1920, 0, 1920, 1080);

        ofSetColor(0, 0, 128);
        ofRect(0, 1080, 1920, 1080);
        ofSetColor(128, 128, 0);
        ofRect(1920, 1080, 1920, 1080);

        ofSetColor(128, 0, 128);
        ofRect(0, 2160, 1920, 1080);
        ofSetColor(0, 128, 128);
        ofRect(1920, 2160, 1920, 1080);

   
    ofPushMatrix();
    northMapping->draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0, 1080);
    southMapping->draw();
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(0, 2160);
    eastMapping->draw();
    ofPopMatrix();
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if(key=='f'){
        ofToggleFullscreen();
    }
    
//    northMapping->keyPressed(key);
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
   // northMapping->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
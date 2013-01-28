#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
   //   ofSetLogLevel(OF_LOG_VERBOSE);
    
    northMapping = new MachineMapping2D();
    northMapping->init(3640, 780, "mapping/xml/shapes.xml");

    southMapping = new MachineMapping2D();
    southMapping->init(3640, 780, "mapping/xml/shapes2.xml");
    
    eastMapping = new MachineMapping2D();
    eastMapping->init(2990, 780, "mapping/xml/shapes3.xml");
    
    fController = faceController();
    fController.loadFaces("night1");

//   receiver.setup(PORT);
}

//--------------------------------------------------------------
void testApp::update(){

/*	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/mouse/position"){
			// both the arguments are int32's
			mouseX = m.getArgAsInt32(0);
			mouseY = m.getArgAsInt32(1);
		}
		// check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			mouseButtonState = m.getArgAsString(0);
		}
		else{
			cout << "message unknown " << m.getAddress() << endl;
		}
	}
 */

    northMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false, 100, -100);
    ofSetColor(255);
     glEnable(GL_DEPTH_TEST);
    fController.draw();
    glDisable(GL_DEPTH_TEST);
    ofPopView();
    northMapping->unbind();

    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false);
    ofSetColor(255);

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
    //ofScale(2, 2);

        ofSetColor(255);
        ofBackground(0);
        

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

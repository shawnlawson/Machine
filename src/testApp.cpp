#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
    ofSetCoordHandedness(OF_RIGHT_HANDED);
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
//    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false, 1000, -1000);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, 3640, 0, ofGetHeight(), 1000, -1000);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    ofSetColor(255);
     glEnable(GL_DEPTH_TEST);
    fController.draw();
    glDisable(GL_DEPTH_TEST);
    ofCircle(3640, 340, 200);
    ofPopView();
    northMapping->unbind();

    eastMapping->bind();
    ofPushView();
    ofViewport(0, 0, 2990, ofGetHeight());
  //  ofSetupScreenOrtho(2990, 780, OF_ORIENTATION_DEFAULT, false, 1000, -1000);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(3640, 3640+2990, 0, ofGetHeight(), 1000, -1000);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    ofSetColor(255);
    glEnable(GL_DEPTH_TEST);
    fController.draw();
    glDisable(GL_DEPTH_TEST);
    ofCircle(3640, 340, 200);
    ofCircle(3640+2990, 340, 100);
    ofPopView();
    eastMapping->unbind();

    
    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
//    ofSetupScreenOrtho(3640, 780, OF_ORIENTATION_DEFAULT, false, 1000, -1000);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(3640+2990, 3640+3640+2990, 0, ofGetHeight(), 1000, -1000);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    ofSetColor(255);
    ofCircle(3640, 340, 200);
    ofCircle(3640+2990, 340, 100);
    ofPopView();
    southMapping->unbind();
    
    
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
    eastMapping->draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0, 2160);
    southMapping->draw();
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

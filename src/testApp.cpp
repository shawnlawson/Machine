#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
    ofSetCoordHandedness(OF_RIGHT_HANDED);
   //   ofSetLogLevel(OF_LOG_VERBOSE);
    
    northMapping = new MachineMapping2D();
    northMapping->init(3640, 780, "mapping/xml/north.xml");
    southMapping = new MachineMapping2D();
    southMapping->init(3640, 780, "mapping/xml/south.xml");
    eastMapping = new MachineMapping2D();
    eastMapping->init(2990, 780, "mapping/xml/east.xml");
    
//    fController = faceController();
//    fController.loadFaces("night1");
//    fController.updateShowState(1);
//    fController.updateShowState(3);


    pController = PolygonController();
    pController.update(4);
    
    eController = EffectController();
    eController.loadShaders();
    
    myLoadSettings();
    
   receiver.setup(PORT);

    blackScreen = BlackScreen();
    
    grid = MyGrid(400, 20);
    grid.loadShader();
    
    myZoom = false;
        
}

//--------------------------------------------------------------
void testApp::update(){

	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/mouse/position"){
			// both the arguments are int32's
//			mouseX = m.getArgAsInt32(0);
//			mouseY = m.getArgAsInt32(1);
		}else if(m.getAddress() == "/mouse/button"){
			//mouseButtonState = m.getArgAsString(0);
		}
		else{
			cout << "message unknown " << m.getAddress() << endl;
		}
	}

    
//    pController.update(0);
//    fController.updateShowState(8);
    eController.update();

    northMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    scene(0);
    ofPopView();
    northMapping->unbind();
    
    eastMapping->bind();
    ofPushView();
    ofViewport(0, 0, 2990, ofGetHeight());
    ofSetupScreenOrtho(2990, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-3640, 0);
    scene(3640);
    ofPopView();
    eastMapping->unbind();
    
    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, 3640, ofGetHeight());
    ofSetupScreenOrtho(3640, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-3640-2990, 0);
    scene(3640+2990);
    ofPopView();
    southMapping->unbind();
}

void testApp::scene(int leftSide){
    ofDisableAlphaBlending();
    glLineWidth(1.5);
    grid.customDraw();

    eController.draw(leftSide, 260, 0.0);

    
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
//    glLineWidth(1.0);
//    pController.draw();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    glEnable(GL_DEPTH_TEST);
//    glPointSize(4);
//    fController.draw();
//    glDisable(GL_DEPTH_TEST);
    

// testing circles
//    ofCircle(3640, 340, 200);
//    ofCircle(3640+2990, 340, 100);
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
  
    ofPushMatrix();
    
    if (!myZoom)
        ofScale( .25, .25);
    else
        ofScale(.9, .9);

    ofBackground(0, 0, 0);
        
        if(drawBackground){
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
        }
       ofDisableAlphaBlending();
    
        ofPushMatrix();
        ofTranslate(northPos);
        northMapping->draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(eastPos);
        eastMapping->draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(southPos);
        southMapping->draw();
        ofPopMatrix();
    
      ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    
    ofPopMatrix();
    float deltaTime = ofGetLastFrameTime();
    
 //   blackScreen.draw(deltaTime);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key) {
        case 'm':
            myZoom = !myZoom;
            break;
            
        case 'f':
            fullscreen = !fullscreen;
            ofSetFullscreen(fullscreen);
            break;
            
        case 'w':
            XML.setValue("mapping:north:x", northPos.x);
            XML.setValue("mapping:north:y", northPos.y);
            XML.setValue("mapping:east:x", eastPos.x);
            XML.setValue("mapping:east:y", eastPos.y);
            XML.setValue("mapping:south:x", southPos.x);
            XML.setValue("mapping:south:y", southPos.y);
            XML.setValue("background:draw", drawBackground);
            XML.setValue("fullscreen", fullscreen);
            XML.saveFile("settings.xml");
            cout << "settings saved" << endl;
            break;
            
        case 'l':
            myLoadSettings();
            break;
            
        case 'b':
            drawBackground = !drawBackground;
            break;
            
        case 'h':
            blackScreen.fadeOut();
            break;
            
        case 'z':
            myMoveMapping = zero;
            break;
            
        case 'n':
            myMoveMapping = north;
            break;
            
        case 'e':
            myMoveMapping = east;
            break;
            
        case 's':
            myMoveMapping = south;
            break;
            
        case 356: // arrow left
			nudgeMappings( 0 );
			break;
		case 358: // arrow right
			nudgeMappings( 1 );
			break;
		case 357: // arrow up
			nudgeMappings( 2 );
			break;
		case 359: // arrow down
			nudgeMappings( 3 );
			break;     
        default:
            break;
            
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

void testApp::nudgeMappings( int direction ){
    if(direction == 0){
        if(north == myMoveMapping)
            northPos.x -= 1.0;
        else if(east == myMoveMapping)
            eastPos.x -= 1.0;
        else if (south == myMoveMapping)
            southPos.x -= 1.0;
        
    }else if(direction == 1){
        if(north == myMoveMapping)
            northPos.x += 1.0;
        else if(east == myMoveMapping)
            eastPos.x += 1.0;
        else if (south == myMoveMapping)
            southPos.x += 1.0;
        
    }else if(direction == 2){
        if(north == myMoveMapping)
            northPos.y -= 1.0;
        else if(east == myMoveMapping)
            eastPos.y -= 1.0;
        else if (south == myMoveMapping)
            southPos.y -= 1.0;
        
    }else if(direction == 3){
        if(north == myMoveMapping)
            northPos.y += 1.0;
        else if(east == myMoveMapping)
            eastPos.y += 1.0;
        else if (south == myMoveMapping)
            southPos.y += 1.0;

    }
}

void testApp::myLoadSettings(){
    if( XML.loadFile("settings.xml") )
		cout << "settings.xml loaded!" << endl;
	else
        cout <<  "unable to load mySettings.xml ... assigned defaults" << endl;
    
    northPos.x = XML.getValue("mapping:north:x", 0);
    northPos.y = XML.getValue("mapping:north:y", 0);
    eastPos.x = XML.getValue("mapping:east:x", 0);
    eastPos.y = XML.getValue("mapping:east:y", 1080);
    southPos.x = XML.getValue("mapping:south:x", 0);
    southPos.y = XML.getValue("mapping:south:y", 2160);
    drawBackground = XML.getValue("background:draw", 1);
    fullscreen = XML.getValue("fullscreen", 0);
    
    myMoveMapping = zero;
    
}

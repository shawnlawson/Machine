#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
 //   ofSetCoordHandedness(OF_RIGHT_HANDED);
   //   ofSetLogLevel(OF_LOG_VERBOSE);
    
    northMapping = new MachineMapping2D();
    northMapping->init(LONG_WALL, HEIGHT_WALL, "mapping/xml/north.xml");
    southMapping = new MachineMapping2D();
    southMapping->init(LONG_WALL, HEIGHT_WALL, "mapping/xml/south.xml");
    eastMapping = new MachineMapping2D();
    eastMapping->init(SHORT_WALL, HEIGHT_WALL, "mapping/xml/east.xml");
    
    fController = faceController();
    fController.loadFaces("night1");
    fController.updateShowState(1, 0.0);
    fController.updateShowState(3, 0.0);

    pController = PolygonController();
    pController.update(RandomFadeIn, 0.0);
    
    banner = new Banner(LONG_WALL, TILE_SIZE*2);
    banner->loadShaders();

    aGrid = new AnimatedGrid( 0, 0);
    aGrid->loadShaders();
    
    blackNorthWest = BlackScreen();
    blackNorthEast = BlackScreen();
    blackEast = BlackScreen();
    blackSouthEast = BlackScreen();
    blackSouthWest = BlackScreen();
    
    buildGUI();
    
    myZoom = false;
    bInit = false;
}

//--------------------------------------------------------------
void testApp::update(){
    if(!bInit){

    }

    float dt  = ofGetLastFrameTime();
    float time = ofGetElapsedTimef();
    
//    pController.update(0, dt);
    fController.updateShowState(SwapFaces, dt);
    banner->update(dt);
    aGrid->update(dt);



    northMapping->bind();
    ofPushView();
    ofViewport(0, 0, LONG_WALL, ofGetHeight());
    ofSetupScreenOrtho(LONG_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    scene(0, LONG_WALL, time);
    ofPopView();
    northMapping->unbind();
    
    eastMapping->bind();
    ofPushView();
    ofViewport(0, 0, SHORT_WALL, ofGetHeight());
    ofSetupScreenOrtho(SHORT_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-LONG_WALL, 0);
    scene(LONG_WALL, SHORT_WALL, time);
    ofPopView();
    eastMapping->unbind();
    
    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, LONG_WALL, ofGetHeight());
    ofSetupScreenOrtho(LONG_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-LONG_WALL-SHORT_WALL, 0);
    scene(LONG_WALL+SHORT_WALL, LONG_WALL, time);
    ofPopView();
    southMapping->unbind();
}

void testApp::scene(int leftSide, int width, float time){
//    ofDisableAlphaBlending();

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    banner->draw(time, leftSide, width, 300);
    aGrid->draw(time, leftSide, width, HEIGHT_WALL);
//    glLineWidth(1.0);
    pController.draw();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    glEnable(GL_DEPTH_TEST);
 //   glPointSize(4);
    fController.draw();
    glDisable(GL_DEPTH_TEST);
    

}

//--------------------------------------------------------------
void testApp::draw(){
  
    ofPushMatrix();
    
    if (!myZoom)
        ofScale( .25, .25);
    else
        ofScale(1.0,1.0);

    ofBackground(0, 0, 0);
        
        if(drawBackground){
            ofSetColor(128, 0, 0);
            ofRect(0, 0, DIM_WIDTH, DIM_HEIGHT);
            ofSetColor(0, 128, 0);
            ofRect(DIM_WIDTH, 0, DIM_WIDTH, DIM_HEIGHT);
            ofSetColor(0, 0, 128);
            ofRect(DIM_WIDTH*2, 0, DIM_WIDTH, DIM_HEIGHT);

            ofSetColor(128, 0, 128);
            ofRect(0, DIM_HEIGHT, DIM_WIDTH, DIM_HEIGHT);
            ofSetColor(0, 128, 128);
            ofRect(DIM_WIDTH, DIM_HEIGHT, DIM_WIDTH, DIM_HEIGHT);
            ofSetColor(128, 128, 0);
            ofRect(DIM_WIDTH*2, DIM_HEIGHT, DIM_WIDTH, DIM_HEIGHT);
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

    float dt = ofGetLastFrameTime();

    blackNorthWest.draw(dt, 0, 0);
    blackNorthEast.draw(dt, DIM_WIDTH, 0);
    blackEast.draw(dt, DIM_WIDTH*2, 0);
    blackSouthEast.draw(dt, DIM_WIDTH, DIM_HEIGHT);
    blackSouthWest.draw(dt, DIM_WIDTH*2, DIM_HEIGHT);
    
    ofPopMatrix();

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
            
        case 'g':
            gui->toggleVisible();
            gui2->toggleVisible();
            gui3->toggleVisible();
            break;
            
        case 's':
            gui->saveSettings("GUI_Settings.xml");
            gui2->saveSettings("GUI_Settings2.xml");
            gui3->saveSettings("GUI_Settings3.xml");
            cout << "settings saved" << endl;
            break;
            
        case 'l':
            gui->loadSettings("GUI_Settings.xml");
            gui2->loadSettings("GUI_Settings2.xml");
            gui3->loadSettings("GUI_Settings3.xml");
            cout << "settings loaded" << endl;
            break;
            
        case 'b':
            drawBackground = !drawBackground;
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

//--------------------------------------------------------------
void testApp::buildGUI()
{ gui = new ofxUICanvas();
    gui->addLabel("The Machine");
    gui->addSpacer();
    gui->addFPS();
    gui->addSpacer();
    gui->addToggle("background", &drawBackground);
    gui->addSpacer();
    gui->add2DPad("North", ofPoint(DIM_WIDTH, DIM_WIDTH+DIM_WIDTH/4),
                  ofPoint(DIM_HEIGHT, DIM_HEIGHT+DIM_HEIGHT/4)
                  , &northPos);
    ((ofxUI2DPad *) gui->getWidget("North"))->setIncrement(1.0);
    gui->add2DPad("East", ofPoint(0, DIM_WIDTH/4),
                  ofPoint(0, DIM_HEIGHT/4), &eastPos);
    ((ofxUI2DPad *) gui->getWidget("East"))->setIncrement(1.0);
    gui->add2DPad("South", ofPoint(DIM_WIDTH, DIM_WIDTH+DIM_WIDTH/4),
                  ofPoint(0, DIM_HEIGHT/4), &southPos);
    ((ofxUI2DPad *) gui->getWidget("South"))->setIncrement(1.0);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    //    gui->setPosition(10, ofGetHeight()-700);
    
    
    gui2 = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH, 0,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, 0);
    gui2->addLabel("Show Control");
    gui2->addSpacer();
    
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent, this, &testApp::guiEvent);
    
    gui3 = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*2, 0,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, 0);
    gui3->addLabel("Blackout");
    vector<string> names;
    names.push_back("offNW");     names.push_back("partialNW");     names.push_back("onNW");
    gui3->addRadio("North_West", names, OFX_UI_ORIENTATION_HORIZONTAL );
    
    names.clear();
    names.push_back("offNE");     names.push_back("partialNE");     names.push_back("onNE");
    gui3->addRadio("North_East", names, OFX_UI_ORIENTATION_HORIZONTAL );
    names.clear();
    names.push_back("offE");     names.push_back("partialE");     names.push_back("onE");
    gui3->addRadio("East", names, OFX_UI_ORIENTATION_HORIZONTAL );
    names.clear();
    names.push_back("offSE");     names.push_back("partialSE");     names.push_back("onSE");
    gui3->addRadio("South_East", names, OFX_UI_ORIENTATION_HORIZONTAL );
    names.clear();
    names.push_back("offSW");     names.push_back("partialSW");     names.push_back("onSW");
    gui3->addRadio("South_West", names, OFX_UI_ORIENTATION_HORIZONTAL );
    gui3->addSpacer(0, 30);
    gui3->addLabel("Banner");
    gui3->addSlider("Banner_Speed", .01, 1.0, &banner->timeScaler);
    names.clear();
    names.push_back("offB");     names.push_back("partialB");     names.push_back("onB");
    gui3->addRadio("Banner_Alpha", names, OFX_UI_ORIENTATION_HORIZONTAL );
    gui3->addSpacer(0, 30);
    gui3->addLabel("Grid");
    gui3->addSlider("Grid_Speed", .01, 1.0, &aGrid->timeScaler);
    names.clear();
    names.push_back("offG");     names.push_back("partialG");     names.push_back("onG");
    gui3->addRadio("Grid_Alpha", names, OFX_UI_ORIENTATION_HORIZONTAL );
        gui3->addSpacer(0, 30);
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent, this, &testApp::guiEvent);
    
    
    gui->loadSettings("GUI_Settings.xml");
    gui2->loadSettings("GUI_Settings2.xml");
    gui3->loadSettings("GUI_Settings3.xml");
    

    
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
//    	cout << "got event from: " << name << endl;
    if( name == "offNW" ){
        blackNorthWest.fadeOut();
    }
    else if( name == "partialNW" ){
        blackNorthWest.fadePartial(128.0);
    }
    else if( name == "onNW" ){
        blackNorthWest.fadeIn();
    }
    else if( name == "offNE" ){
        blackNorthEast.fadeOut();
    }
    else if( name == "partialNE" ){
        blackNorthEast.fadePartial(128.0);
    }
    else if( name == "onNE" ){
        blackNorthEast.fadeIn();
    }
    else if( name == "offE" ){
        blackEast.fadeOut();
    }
    else if( name == "partialE" ){
        blackEast.fadePartial(128.0);
    }
    else if( name == "onE" ){
        blackEast.fadeIn();
    }
    else if( name == "offSW" ){
        blackSouthWest.fadeOut();
    }
    else if( name == "partialSW" ){
        blackSouthWest.fadePartial(128.0);
    }
    else if( name == "onSW" ){
        blackSouthWest.fadeIn();
    }
    else if( name == "offSE" ){
        blackSouthEast.fadeOut();
    }
    else if( name == "partialSE" ){
        blackSouthEast.fadePartial(128.0);
    }
    else if( name == "onSE" ){
        blackSouthEast.fadeIn();
    }
    else if( name == "offB" ){
        banner->fadeOut();
    }
    else if( name == "partialB" ){
        banner->fadePartial(0.5);
    }
    else if( name == "onB" ){
        banner->fadeIn();
    }
    else if( name == "offG" ){
        aGrid->fadeOut();
    }
    else if( name == "partialG" ){
        aGrid->fadePartial(0.5);
    }
    else if( name == "onG" ){
        aGrid->fadeIn();
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    gui->saveSettings("GUI_Settings.xml");
    gui2->saveSettings("GUI_Settings2.xml");
    gui3->saveSettings("GUI_Settings3.xml");
    delete gui;
}
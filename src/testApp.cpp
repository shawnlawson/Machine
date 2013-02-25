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
    fController.updateShowState(AllFacesPopulate, 0.0);
    fController.updateShowState(AllOpaqueFade, .01);

    pController = PolygonController();
  //  pController.update(AllOpaqueFade, 0.0);
    
    banner = new Banner(LONG_WALL, TILE_SIZE*2);
    banner->loadShaders();

    aGrid = new AnimatedGrid( 0, 0);
    aGrid->loadShaders();
    
    blackNorthWest = BlackScreen();
    blackNorthEast = BlackScreen();
    blackEast = BlackScreen();
    blackSouthEast = BlackScreen();
    blackSouthWest = BlackScreen();
    
    northGame = new GameOfLife(LONG_WALL, HEIGHT_WALL);
    eastGame  = new GameOfLife(SHORT_WALL, HEIGHT_WALL);
    southGame = new GameOfLife(LONG_WALL, HEIGHT_WALL);
    northGame->loadShader();
    eastGame->loadShader();
    southGame->loadShader();
    
    
    buildGUI();
    
    myZoom = false;
    bInit = false;
}

//--------------------------------------------------------------
void testApp::update()
{
    float dt  = ofGetLastFrameTime();
    float time = ofGetElapsedTimef();

    if(!bInit){
        
        bInit = true;
    }
    
    pController.update(0, dt);
    fController.updateShowState(SwapFaces, dt);
    banner->update(dt);
    aGrid->update(dt);

    northGame->update(dt);
    eastGame->update(dt);
    southGame->update(dt);
    


    northMapping->bind();
    ofPushView();
    ofViewport(0, 0, LONG_WALL, ofGetHeight());
    ofSetupScreenOrtho(LONG_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    scene(0, LONG_WALL, time);
    
    northGame->draw(0, 0);
    ofPopView();
    northMapping->unbind();
        ofSetColor(255);
    eastMapping->bind();
    ofPushView();
    ofViewport(0, 0, SHORT_WALL, ofGetHeight());
    ofSetupScreenOrtho(SHORT_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-LONG_WALL, 0);
    scene(LONG_WALL, SHORT_WALL, time);
    ofSetColor(255);
    eastGame->draw(LONG_WALL, 0);
    ofPopView();
    eastMapping->unbind();
    
    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, LONG_WALL, ofGetHeight());
    ofSetupScreenOrtho(LONG_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-LONG_WALL-SHORT_WALL, 0);
    scene(LONG_WALL+SHORT_WALL, LONG_WALL, time);
    ofSetColor(255);
    southGame->draw(LONG_WALL+SHORT_WALL, 0);
    ofPopView();
    southMapping->unbind();
}

void testApp::scene(int leftSide, int width, float time){

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    banner->draw(time, leftSide, width, 300);

    aGrid->draw(time, leftSide, width, HEIGHT_WALL);

    pController.draw();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    glEnable(GL_DEPTH_TEST);
    fController.draw();
    glDisable(GL_DEPTH_TEST);
    

}

//--------------------------------------------------------------
void testApp::draw()
{  
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
            gui4->saveSettings("GUI_Settings4.xml");
            cout << "settings saved" << endl;
            break;
            
        case 'l':
            gui->loadSettings("GUI_Settings.xml");
            gui2->loadSettings("GUI_Settings2.xml");
            gui3->loadSettings("GUI_Settings3.xml");
            gui4->loadSettings("GUI_Settings4.xml");
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
{
    gui = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*5, ofGetHeight()-DIM_HEIGHT,
                          OFX_UI_GLOBAL_CANVAS_WIDTH, DIM_HEIGHT);
    gui->addLabel("The Machine");
    gui->addSpacer();
    gui->addFPS();
    gui->addSpacer();
    gui->addToggle("background", &drawBackground);
    gui->addSpacer();
    gui->add2DPad("North", ofPoint(DIM_WIDTH, DIM_WIDTH+DIM_WIDTH/4),
                  ofPoint(DIM_HEIGHT, DIM_HEIGHT+DIM_HEIGHT/2)
                  , &northPos);
    ((ofxUI2DPad *) gui->getWidget("North"))->setIncrement(1.0);
    gui->add2DPad("East", ofPoint(0, DIM_WIDTH/4),
                  ofPoint(0, DIM_HEIGHT/2), &eastPos);
    ((ofxUI2DPad *) gui->getWidget("East"))->setIncrement(1.0);
    gui->add2DPad("South", ofPoint(DIM_WIDTH, DIM_WIDTH+DIM_WIDTH/4),
                  ofPoint(0, DIM_HEIGHT/2), &southPos);
    ((ofxUI2DPad *) gui->getWidget("South"))->setIncrement(1.0);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui2 = new ofxUICanvas(0, ofGetHeight()-DIM_HEIGHT,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, DIM_HEIGHT);
    gui2->addLabel("Show Control");
    gui2->addSpacer();
    
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent, this, &testApp::guiEvent);
    
    gui3 = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*2, ofGetHeight()-DIM_HEIGHT,
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
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Banner");
    gui3->addSlider("Banner_Speed", .01, 5.0, &banner->timeScaler);
    gui3->addSlider("Banner_Alpha", 0.0, 1.0, 1.0);
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Grid");
    gui3->addSlider("Grid_Speed", .01, 2.0, &aGrid->timeScaler);
    gui3->addSlider("GridWave_Alpha", 0.0, 8.0, 2.0);
    gui3->addSlider("Grid_Alpha", 0.0, 1.0, 1.0);
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Raven");
    gui3->addSlider("Raven_Speed", .001, .1, &pController.timeScaler);
    gui3->addSlider("Raven_Alpha", 0.0, 1.0, 1.0);
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Faces");
    gui3->addToggle("colorF", false);
    names.clear();
    names.push_back("pointF");     names.push_back("wireF");     names.push_back("triF");
    gui3->addRadio("Face_Style", names, OFX_UI_ORIENTATION_HORIZONTAL );
    gui3->addSlider("pointSizeF", 0.0, 10.0, &fController.vertexSize);
    gui3->addSlider("lineWidthF", 0.0, 10.0, &fController.lineWidth);
    
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent, this, &testApp::guiEvent);
    
    gui4 = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*2, ofGetHeight()-DIM_HEIGHT,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, 0);
    gui4->addLabel("stuff");
    
    gui4->autoSizeToFitWidgets();
    ofAddListener(gui4->newGUIEvent, this, &testApp::guiEvent);
    
    gui->loadSettings("GUI_Settings.xml");
    gui2->loadSettings("GUI_Settings2.xml");
    gui3->loadSettings("GUI_Settings3.xml");
    gui4->loadSettings("GUI_Settings4.xml");  
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
    else if( name == "Banner_Alpha" ){
        banner->alpha.reset( ((ofxUISlider *)e.widget)->getValue());
    }
    else if( name == "Grid_Alpha" ){
        aGrid->alpha.reset( ((ofxUISlider *)e.widget)->getValue() );
    }
    else if( name == "GridWave_Alpha" ){
        cout << ((ofxUISlider *)e.widget)->getValue() << endl;
        aGrid->waveAlpha.reset( ((ofxUISlider *)e.widget)->getValue());
        
    }
    else if( name == "Raven_Alpha" ){
        pController.assignAlpha(((ofxUISlider *)e.widget)->getValue());
    }

    else if( name == "colorF" ){
        if( ((ofxUIToggle *)e.widget)->getValue() )
            fController.whiteOut.animateTo(0.0);
        else
            fController.whiteOut.animateTo(1.0);
    }
    else if( name == "pointF" ){
        fController.setMode(OF_MESH_POINTS);
    }
    else if( name == "wireF" ){
        fController.setMode(OF_MESH_WIREFRAME);
    }
    else if( name == "triF" ){
        fController.setMode(OF_MESH_FILL);
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    delete gui, gui2, gui3, gui4, northMapping, southMapping, eastMapping, banner, aGrid, northGame, eastGame, southGame;
}
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
   fController.updateShowState(AllTransparentNow, 0.0);

    pController = PolygonController();
    
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
    
    joanna = Joanna();
    joanna.loadFaces();
    
    pixelate.load("shaders/pixelate");
    pixelSize = 1.0;
    
    aGridDur = 60.0;
    aGridWaveDur = 60.0;
    ravenDur = 45.0;
    faceWhiteDur = 10.0;
    faceVertexDur = 10.0;
    faceRandomDur = 15.0;
    jWhiteDur = 5.0;
    jVertexDur = 5.0;
    jRandomDur = 5.0;
    faceReEmergeDur = 15.0;
    jRandomOutDur = 15.0;
    GOLDur = 15.0;
    
    buildGUI();
    
    myZoom = false;
    bBannerOn = false;
    bGridOn = false;
    bRavenOn = false;
    bGameOn = false;
    bFacesOn = false;
    bJoannaOn = false;
    bPixelateOn = false;
    facesLoading = false;
}

//--------------------------------------------------------------
void testApp::update()
{
    float dt  = ofGetLastFrameTime();
    float time = ofGetElapsedTimef();
    
//    if(facesLoading){
//        ((ofxUITextArea *)gui2->getWidget("loaded: "))->setTextString(ofToString(fController.loaded)+" of "+ofToString(fController.totalToLoad));
//    }
    
    if (bRavenOn)   pController.update(0, dt);
    if (bFacesOn)   fController.update(dt);
    if (bBannerOn)  banner->update(dt);
    if (bGridOn)    aGrid->update(dt);
    if (bGameOn) {
        northGame->update(dt);
        eastGame->update(dt);
        southGame->update(dt);
    }
    if (bJoannaOn)  {
        joanna.update(dt);
    }
    if(bPixelateOn) pixelSize = ofClamp(pixelSize + ofSignedNoise(ofGetElapsedTimef())*5.0,
                                        1.0, 100.0);

    northMapping->bind();
    ofPushView();
    ofViewport(0, 0, LONG_WALL, ofGetHeight());
    ofSetupScreenOrtho(LONG_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    if (bGameOn)  northGame->draw(0, 0);
    scene(0, LONG_WALL, time);
    ofPopView();
    northMapping->unbind();
//--
    eastMapping->bind();
    ofPushView();
    ofViewport(0, 0, SHORT_WALL, ofGetHeight());
    ofSetupScreenOrtho(SHORT_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-LONG_WALL, 0);
    if (bGameOn) eastGame->draw(LONG_WALL, 0);
    scene(LONG_WALL, SHORT_WALL, time);
    ofPopView();
    eastMapping->unbind();
//--
    southMapping->bind();
    ofPushView();
    ofViewport(0, 0, LONG_WALL, ofGetHeight());
    ofSetupScreenOrtho(LONG_WALL, ofGetHeight(), OF_ORIENTATION_DEFAULT, false, -1000, 3000);
    ofTranslate(-LONG_WALL-SHORT_WALL, 0);
    if (bGameOn) southGame->draw(LONG_WALL+SHORT_WALL, 0);
    scene(LONG_WALL+SHORT_WALL, LONG_WALL, time);
    ofPopView();
    southMapping->unbind();
}

void testApp::scene(int leftSide, int width, float time){

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if (bBannerOn)  banner->draw(time, leftSide, width, 300);
    if (bGridOn)    aGrid->draw(time, leftSide, width, HEIGHT_WALL);
    if (bRavenOn)   pController.draw();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if(bFacesOn){
        glEnable(GL_DEPTH_TEST);
        fController.draw();
        glDisable(GL_DEPTH_TEST);
    }
    
    if(bJoannaOn){
        glEnable(GL_DEPTH_TEST);
        joanna.draw();
        glDisable(GL_DEPTH_TEST);
    }

}

//--------------------------------------------------------------
void testApp::draw()
{  
    ofPushMatrix();
    
    if (!myZoom)
        ofScale( .25, .25);
    else
        ofScale(1.0,1.0);

    ofBackground(0);
        
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
    if( bPixelateOn ){
        pixelate.begin();
//        pixelate.setUniformTexture("tex0", northMapping->_fbo.getTextureReference(), 0);

        pixelate.setUniform1f("pixel_size", pixelSize);
    }
        northMapping->draw();
    if (bPixelateOn)        pixelate.end();
        ofPopMatrix();
    

    
        ofPushMatrix();
        ofTranslate(eastPos);
    if( bPixelateOn ){
        pixelate.begin();
        //        pixelate.setUniformTexture("tex0", eastMapping->_fbo.getTextureReference(), 0);
        pixelate.setUniform1f("pixel_size", pixelSize);
    }
        eastMapping->draw();
        if (bPixelateOn)        pixelate.end();
        ofPopMatrix();
    


        ofPushMatrix();
        ofTranslate(southPos);
    if( bPixelateOn ){
                pixelate.begin();
        //        pixelate.setUniformTexture("tex0", southMapping->_fbo.getTextureReference(), 0);
        pixelate.setUniform1f("pixel_size", pixelSize);
    }
        southMapping->draw();
        if( bPixelateOn ) pixelate.end();
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
            if(fullscreen){
                gui->setPosition(OFX_UI_GLOBAL_CANVAS_WIDTH*5, DIM_HEIGHT);
                gui2->setPosition(0, DIM_HEIGHT);
                gui3->setPosition(OFX_UI_GLOBAL_CANVAS_WIDTH*2, DIM_HEIGHT);
                gui4->setPosition(OFX_UI_GLOBAL_CANVAS_WIDTH*3, DIM_HEIGHT);
            }else{
                gui->setPosition(OFX_UI_GLOBAL_CANVAS_WIDTH*5, 0);
                gui2->setPosition(0, 0);
                gui3->setPosition(OFX_UI_GLOBAL_CANVAS_WIDTH*2, 0);
                gui4->setPosition(OFX_UI_GLOBAL_CANVAS_WIDTH*3, 0);
            }
                
            break;
            
        case 'g':
            gui->toggleVisible();
            gui2->toggleVisible();
            gui3->toggleVisible();
            gui4->toggleVisible();
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
    gui = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*5, 0,
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
    
    gui2 = new ofxUICanvas(0, 0,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, DIM_HEIGHT);
    gui2->addLabel("Show Control");
    gui2->addSpacer();
    vector<string> names;
    names.clear();
    names.push_back("reset_all");
    names.push_back("present_scene4");
    names.push_back("grid_emerge");
    names.push_back("pattern_emerge");
    names.push_back("raven_emerge");
    names.push_back("faces_emerge");
    names.push_back("scrim_black");
    names.push_back("failing_machine");
    names.push_back("blackout_now");
    names.push_back("joanna_emerge");
    names.push_back("faces_reemerge");
    names.push_back("gol_emerge");
    gui2->addRadio("Show Cues", names, OFX_UI_ORIENTATION_VERTICAL );
    gui2->addSpacer(); gui2->addSpacer();
    gui2->addMinimalSlider("aGridDur", 1.0, 120.0, &aGridDur);
    gui2->addMinimalSlider("aGridWaveDur", 1.0, 120.0, &aGridWaveDur);
    gui2->addMinimalSlider("ravenDur", 1.0, 120.0, &ravenDur);
    gui2->addMinimalSlider("faceWhiteDur", 1.0, 120.0, &faceWhiteDur);
    gui2->addMinimalSlider("faceVertexDur", 1.0, 120.0, &faceVertexDur);
    gui2->addMinimalSlider("faceRandomDur", 1.0, 120.0, &faceRandomDur);
    gui2->addMinimalSlider("jWhiteDur", 1.0, 120.0, &jWhiteDur);
    gui2->addMinimalSlider("jVertexDur", 1.0, 120.0, &jVertexDur);
    gui2->addMinimalSlider("faceReEmergeDur", 1.0, 120.0, &faceReEmergeDur);
    gui2->addMinimalSlider("jRandomOutDur", 1.0, 120.0, &jRandomOutDur);
    gui2->addMinimalSlider("GOLDur", 1.0, 120.0, &GOLDur);
//    gui2->addSpacer(); gui2->addSpacer();
//    gui2->addLabelButton("load_images", false);
//    gui2->addTextArea("loaded: ", "0 of 0");
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent, this, &testApp::guiEvent);
    
    gui3 = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*2, 0,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, 0);
    
    gui3->addLabel("Banner");
    gui3->addToggle("Banner_On_Off", &bBannerOn);
    gui3->addMinimalSlider("Banner_Speed", .01, 5.0, &banner->timeScaler);
    gui3->addMinimalSlider("Banner_Alpha", 0.0, 1.0, 1.0);
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Grid");
    gui3->addToggle("Grid_On_Off", &bGridOn);
    gui3->addMinimalSlider("Grid_Speed", .01, 2.0, &aGrid->timeScaler);
    gui3->addMinimalSlider("Grid_Alpha", 0.0, 1.0, 1.0);
    gui3->addMinimalSlider("GridWave_Alpha", 0.0, 1.0, .2);
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Raven");
    gui3->addToggle("Raven_On_Off", &bRavenOn);
    gui3->addMinimalSlider("Raven_Speed", .001, .1, &pController.timeScaler);
    gui3->addMinimalSlider("Raven_Alpha", 0.0, 1.0, 1.0);
    gui3->addSpacer();gui3->addSpacer();
    
    gui3->addLabel("Faces");
    gui3->addToggle("Faces_On_Off", &bFacesOn);
    gui3->addMinimalSlider("Faces Bright", 0.0, 1.0, 1.0);
    names.clear();
    names.push_back("pointF");     names.push_back("wireF");     names.push_back("triF");
    gui3->addRadio("Face_Style", names, OFX_UI_ORIENTATION_HORIZONTAL );
    gui3->addMinimalSlider("pointSizeF", 0.0, 10.0, 1.0);
    gui3->addMinimalSlider("lineWidthF", 0.0, 10.0, &fController.lineWidth);
    gui3->addToggle("Swap Faces", &fController.swapFaces);
    names.clear();
    names.push_back("Now Transparent F");
    names.push_back("Now Opaque F");
    names.push_back("Random Transparent F");
    names.push_back("Random Opaque F");
    names.push_back("Gradual Transparent F");
    names.push_back("Gradual Opaque F");
    gui3->addDropDownList("Faces Alpha", names);
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent, this, &testApp::guiEvent);
    
    gui4 = new ofxUICanvas(OFX_UI_GLOBAL_CANVAS_WIDTH*3, 0,
                           OFX_UI_GLOBAL_CANVAS_WIDTH, 0);
    gui4->addLabel("Blackout");
    gui4->addMinimalSlider("All_Walls", 0.0, 1.0, 1.0);
    gui4->addMinimalSlider("North_West", 0.0, 1.0, 1.0);
    gui4->addMinimalSlider("North_East", 0.0, 1.0, 1.0);
    gui4->addMinimalSlider("East", 0.0, 1.0, 1.0);
    gui4->addMinimalSlider("South_East", 0.0, 1.0, 1.0);
    gui4->addMinimalSlider("South_West", 0.0, 1.0, 1.0);
    gui4->addSpacer();gui4->addSpacer();
    gui4->addLabel("Game_Of_Life");
    gui4->addToggle("Game_On_Off", &bGameOn);
    gui4->addLabelButton("Game_Regenerate", false);
    gui4->addMinimalSlider("Game_Alpha", 0.0, 1.0, 1.0);
    gui4->addSpacer();gui4->addSpacer();
    gui4->addLabel("Pixelate");
    gui4->addToggle("Pixelate_On_Off", &bPixelateOn);
    gui4->addMinimalSlider("Pixel_Size", 1.0, 100.0, &pixelSize);
    gui4->addSpacer();gui4->addSpacer();
    gui4->addLabel("Joanna");
    gui4->addToggle("Joanna_On_Off", &bJoannaOn);
    gui4->addMinimalSlider("Joanna Bright", 0.0, 1.0, 1.0);
    names.clear();
    names.push_back("JpointF");     names.push_back("JwireF");     names.push_back("JtriF");
    gui4->addRadio("Joanna_Style", names, OFX_UI_ORIENTATION_HORIZONTAL );
    gui4->addMinimalSlider("JpointSizeF", 0.0, 15.0, 2.0);
    gui4->addMinimalSlider("JlineWidthF", 0.0, 10.0, &joanna.lineWidth);
    names.clear();
    names.push_back("Now Transparent");
    names.push_back("Now Opaque");
    names.push_back("Random Transparent");
    names.push_back("Random Opaque");
    names.push_back("Gradual Transparent");
    names.push_back("Gradual Opaque");
    gui4->addDropDownList("Joanna Alpha", names);
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
    if( name == "All_Walls" ){
        ((ofxUISlider *)gui4->getWidget("North_West"))->setValue( ((ofxUISlider *)e.widget)->getValue());
        blackNorthWest.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
        ((ofxUISlider *)gui4->getWidget("North_East"))->setValue( ((ofxUISlider *)e.widget)->getValue());
        blackNorthEast.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
        ((ofxUISlider *)gui4->getWidget("East"))->setValue( ((ofxUISlider *)e.widget)->getValue());
        blackEast.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
        ((ofxUISlider *)gui4->getWidget("South_West"))->setValue( ((ofxUISlider *)e.widget)->getValue());
        blackSouthWest.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
        ((ofxUISlider *)gui4->getWidget("South_East"))->setValue( ((ofxUISlider *)e.widget)->getValue());
        blackSouthEast.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
    }
    if( name == "North_West" ){
        blackNorthWest.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
    }
    else if( name == "North_East" ){
        blackNorthEast.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
    }
    else if( name == "East" ){
        blackEast.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
    }
    else if( name == "South_West" ){
        blackSouthWest.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
    }
    else if( name == "South_East" ){
        blackSouthEast.alpha.reset( ((ofxUISlider *)e.widget)->getValue()*255 );
    }
    else if( name == "Banner_Alpha" ){
        banner->alpha.reset( ((ofxUISlider *)e.widget)->getValue());
    }
    else if( name == "Grid_Alpha" ){
        aGrid->alpha.reset( ((ofxUISlider *)e.widget)->getValue() );
    }
    else if( name == "GridWave_Alpha" ){
        aGrid->waveAlpha.reset( ((ofxUISlider *)e.widget)->getValue()*10.0);
    }
    else if( name == "Raven_Alpha" ){
        pController.assignAlpha(((ofxUISlider *)e.widget)->getValue());
    }
    else if( name == "Faces Bright" ){
        fController.whiteOut.reset(((ofxUISlider *)e.widget)->getValue());
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
    else if( name == "pointSizeF" ){
        fController.vertexSize.reset(((ofxUISlider *)e.widget)->getValue());
    }
    else if( name == "Game_Alpha" ){
        float val = ((ofxUISlider *)e.widget)->getValue();
        northGame->alpha.reset( val );
        eastGame->alpha.reset( val );
        southGame->alpha.reset( val );
    }
    else if( name == "Game_Regenerate" ){
        if(((ofxUISlider *)e.widget)->getValue()){
            northGame->regenerate();
            eastGame->regenerate();
            southGame->regenerate();
        }
    }
    else if(name == "Joanna Bright"){
        joanna.whiteOut.reset(((ofxUISlider *)e.widget)->getValue());
    }
    else if( name == "JpointF" ){
        joanna.setMode(OF_MESH_POINTS);
    }
    else if( name == "JwireF" ){
        joanna.setMode(OF_MESH_WIREFRAME);
    }
    else if( name == "JtriF" ){
        joanna.setMode(OF_MESH_FILL);
    }
    else if( name == "JpointSizeF"){
        joanna.vertexSize.reset(((ofxUISlider *)e.widget)->getValue());
    }
    else if( name == "Now Transparent"){
        joanna.updateAlpha(AllTransparentNow, 0.0);
    }
    else if( name == "Now Opaque"){
        joanna.updateAlpha(AllOpaqueNow, 0.0);
    }
    else if( name == "Random Transparent"){
        joanna.updateAlpha(RandomFadeOut, 5.0);
    }
    else if( name == "Random Opaque"){
        joanna.updateAlpha(RandomFadeIn, 5.0);
    }
    else if( name == "Gradual Transparent"){
        joanna.updateAlpha(AllTransparentFade, 0.0);
    }
    else if( name == "Gradual Opaque"){
        joanna.updateAlpha(AllOpaqueFade, 0.0);
    }
    else if( name == "Now Transparent F"){
        fController.updateShowState(AllTransparentNow, 0.0);
    }
    else if( name == "Now Opaque F"){
        fController.updateShowState(AllOpaqueNow, 0.0);
    }
    else if( name == "Random Transparent F"){
        fController.updateShowState(RandomFadeOut, 0.0);
    }
    else if( name == "Random Opaque F"){
        fController.updateShowState(RandomFadeIn, 0.0);
    }
    else if( name == "Gradual Transparent F"){
        fController.updateShowState(AllTransparentFade, 0.0);
    }
    else if( name == "Gradual Opaque F"){
        fController.updateShowState(AllOpaqueFade, 0.0);
    }
    else if (name == "load_images"){
        facesLoading = true;
        fController.loadFaces("night1");
        fController.updateShowState(AllFacesPopulate, 0.0);
        fController.updateShowState(AllTransparentNow, 0.0);
    }
    else if( name == "reset_all"){
        banner->alpha.reset(0.0);
        banner->timeScaler = 0.1;
        aGrid->alpha.reset(0.0);
        aGrid->timeScaler = 0.1;
        aGrid->waveAlpha.reset(0.0);
        pController.assignAlpha(0.0);
        pController.timeScaler = 0.01;
        fController.updateShowState(AllTransparentNow, 0.0);
        fController.whiteOut.reset(1.0);
        fController.vertexSize.reset(2.0);
        fController.setMode(OF_MESH_POINTS);
        blackNorthEast.alpha.reset(0.0);
        blackNorthWest.alpha.reset(0.0);
        blackEast.alpha.reset(0.0);
        blackSouthEast.alpha.reset(0.0);
        blackSouthWest.alpha.reset(0.0);
        joanna.updateAlpha(AllTransparentNow, 0.0);
        joanna.whiteOut.reset(1.0);
        joanna.vertexSize.reset(2.0);
        joanna.setMode(OF_MESH_POINTS);
        northGame->alpha.reset(0.0);
        eastGame->alpha.reset(0.0);
        southGame->alpha.reset(0.0);
        pixelSize = ofRandom(5);
        bBannerOn = false;
        bGridOn = false;
        bRavenOn = false;
        bGameOn = false;
        bFacesOn = false;
        bJoannaOn = false;
        bPixelateOn = false;
    }
    else if( name == "present_scene4"){
        banner->alpha.reset(0.0);
        banner->alpha.setDuration(1.0);
        bBannerOn = true;
        banner->alpha.animateTo(1.0);
        banner->timeScaler = .1;
    }
    else if( name == "grid_emerge"){
        aGrid->alpha.reset(0.0);
        aGrid->alpha.setDuration(aGridDur);
        bGridOn = true;
        aGrid->alpha.animateTo(1.0);
    }
    else if(name == "pattern_emerge"){
        aGrid->waveAlpha.reset(0.0);
        aGrid->timeScaler = 0.1;
        aGrid->waveAlpha.setDuration(aGridWaveDur);
        aGrid->waveAlpha.animateTo(8.0);
    }
    else if(name == "raven_emerge"){
        pController.assignAlpha(0.0);
        pController.assignLength(ravenDur);
        pController.timeScaler = 0.01;
        bRavenOn = true;
        pController.randomFadeIn(0.0, 10.0);
    }
    else if(name == "faces_emerge"){
        fController.updateShowState(AllTransparentNow, 0.0);
        fController.whiteOut.reset(1.0);
        fController.whiteOut.setDuration(faceWhiteDur);
        fController.vertexSize.reset(2.0);
        fController.vertexSize.setDuration(faceVertexDur);
        fController.setMode(OF_MESH_POINTS);
        bFacesOn = true;
        fController.updateShowState(RandomFadeIn, faceRandomDur);
        fController.whiteOut.animateToAfterDelay(0.0, faceRandomDur);
        fController.vertexSize.animateToAfterDelay(7.0, faceRandomDur+faceWhiteDur);
    }
    else if( name == "scrim_black"){
        blackNorthEast.alpha.reset(0.0);
        blackNorthWest.alpha.reset(0.0);
        blackEast.alpha.reset(0.0);
        blackSouthEast.alpha.reset(0.0);
        blackSouthWest.alpha.reset(0.0);
        
        blackNorthEast.alpha.setDuration(20.0);
        blackNorthWest.alpha.setDuration(20.0);
        blackEast.alpha.setDuration(20.0);
        blackSouthEast.alpha.setDuration(20.0);
        blackSouthWest.alpha.setDuration(20.0);
        
        blackNorthEast.alpha.animateTo(255.0);
        blackNorthWest.alpha.animateTo(255.0);
        blackEast.alpha.animateTo(255.0);
        blackSouthEast.alpha.animateTo(255.0);
        blackSouthWest.alpha.animateTo(255.0);
    }
    else if( name == "failing_machine"){
        pixelSize = ofRandom(5);
        blackNorthEast.alpha.reset(0.0);
        blackNorthWest.alpha.reset(0.0);
        blackEast.alpha.reset(0.0);
        blackSouthEast.alpha.reset(0.0);
        blackSouthWest.alpha.reset(0.0);

        banner->alpha.reset(1.0);
        banner->timeScaler = 4.0;
        aGrid->alpha.reset(1.0);
        aGrid->waveAlpha.reset(1.0);
        aGrid->timeScaler = 4.0;
        pController.assignAlpha(1.0);
        pController.timeScaler = 0.01;
        bPixelateOn = true;
    }
    else if( name == "blackout_now"){
        blackNorthEast.alpha.reset(255.0);
        blackNorthWest.alpha.reset(255.0);
        blackEast.alpha.reset(255.0);
        blackSouthEast.alpha.reset(255.0);
        blackSouthWest.alpha.reset(255.0);
        bBannerOn = false;
        bGridOn = false;
        bRavenOn = false;
        bGameOn = false;
        bFacesOn = false;
        bJoannaOn = false;
        bPixelateOn = false;
    }
    else if( name == "joanna_emerge"){
        blackNorthEast.alpha.reset(0.0);
        blackNorthWest.alpha.reset(0.0);
        blackEast.alpha.reset(0.0);
        blackSouthEast.alpha.reset(0.0);
        blackSouthWest.alpha.reset(0.0);
        joanna.updateAlpha(AllTransparentNow, 0.0);
        joanna.whiteOut.reset(1.0);
        joanna.whiteOut.setDuration(jWhiteDur);
        joanna.vertexSize.reset(2.0);
        joanna.vertexSize.setDuration(jVertexDur);
        joanna.setMode(OF_MESH_POINTS);
        bJoannaOn = true;
        joanna.updateAlpha(RandomFadeIn, jRandomDur);
        joanna.whiteOut.animateToAfterDelay(0.0, jRandomDur);
        joanna.vertexSize.animateToAfterDelay(7.0, jRandomDur+jWhiteDur);
    }
    else if( name == "faces_reemerge"  ){
        fController.updateShowState(AllTransparentNow, 0.0);
        fController.setMode(OF_MESH_FILL);
        bFacesOn = true;
        fController.updateShowState(RandomFadeIn, faceReEmergeDur);
        joanna.updateAlpha(RandomFadeOut, jRandomOutDur);
    }
    else if( name == "gol_emerge" ){
        northGame->alpha.reset(0.0);
        eastGame->alpha.reset(0.0);
        southGame->alpha.reset(0.0);
        northGame->alpha.setDuration(GOLDur);
        eastGame->alpha.setDuration(GOLDur);
        southGame->alpha.setDuration(GOLDur);
        bGameOn = true;
        northGame->alpha.animateTo(1.0);
        eastGame->alpha.animateTo(1.0);
        southGame->alpha.animateTo(1.0);
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    delete gui, gui2, gui3, gui4, northMapping, southMapping, eastMapping, banner, aGrid, northGame, eastGame, southGame;
}
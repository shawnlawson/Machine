//
//  myLoadingLabel.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/28/13.
//
//

#ifndef TheMachine_myLoadingLabel_h
#define TheMachine_myLoadingLabel_h

class myLoadingLabel : public ofxUILabel

ofxUIFPS(float x, float y, int _size) : ofxUILabel()
{
    rect = new ofxUIRectangle(x,y,0,0);
    init("Loading", "0 of 0", _size);
    kind = 100;
    labelPrecision = 3;
    autoSize = true;
}

ofxUIFPS(int _size) : ofxUILabel()
{
    rect = new ofxUIRectangle(0,0,0,0);
    init("Loading", "0 of 0", _size);
    kind = 100;
    labelPrecision = 3;
    autoSize = true;
}

void update()
{
    setLabel("FPS: " + ofToString(ofGetFrameRate(), labelPrecision));
}

void setLabelPrecision(int _precision) {
    labelPrecision = _precision;
}


protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
int labelPrecision;
};

#endif

#endif

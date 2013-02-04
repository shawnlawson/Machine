//
//  MyGrid.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/3/13.
//
//

class MyGrid : public ofNode, ofVboMesh{

public:
    vector<ofVec2f> points;
     ofShader distanceBlacken;
    
    MyGrid(int wDivisions = 10, int hDivisions = 10){
    
//        for (int y = 0; y<hDivisions; y++) {
//            for(int x = 0; x<wDivisions; x++){
//                ofVec3f nw = ofVec3f(x, y, 0);
//                ofVec3f ne = ofVec3f(x + 1, y, 0);
//                ofVec3f sw = ofVec3f(x, y + 1, 0);
//                ofVec3f se = ofVec3f(x + 1, y + 1, 0);
//                
//                addFace(nw, ne, se, sw);
//            }
//        }
//
        
        int l = wDivisions/-2;
        int r = wDivisions/2;
        float s = .03;
        float t = hDivisions-1.0;

        for (int i = l; i<r; i++) {
            points.push_back(ofVec2f(i, 0.0));
            points.push_back(ofVec2f(i, (t-log(t)-t*1.1)));
//              ofLine(i, 0, i+i*s, -3); //vertical lines
            //      ofLine(i, 0, i, -3);
        }
        for( int i=0;i<hDivisions; i++){
            float tY = (i-log(i)-i*1.1);
            points.push_back(ofVec2f(-200.0, tY));
            points.push_back(ofVec2f(200.0, tY));
       //     ofLine(-d*5, tY, d*5, tY); //horizontal
        }
        
        setScale(30, 35, 30);//, 500, 400);
        setPosition(5135, 782, 0);
    }

    void loadShader(){
          distanceBlacken.load("shaders/distanceBlacken");
    }
    

    //--------------------------------------------------------------
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c) {
        addVertex(a);
        addVertex(b);
        addVertex(c);
    }

    //--------------------------------------------------------------
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
        addFace(a, b, c);
        addFace(a, c, d);
    }

    //--------------------------------------------------------------
    void update(){
        
    }

    //--------------------------------------------------------------
    void customDraw(){
       // rotate(.05, 1, 0, 0);
        distanceBlacken.begin();
        transformGL();
        ofSetColor( 255, 255, 255, 255);
        for(int i=0; i<points.size(); i+=2)
            ofLine(points[i], points[i+1]);
        restoreTransformGL();
        distanceBlacken.end();
       
    }

};
//
//  MyConstants.h
//  TheMachine
//
//  Created by Shawn Lawson on 2/24/13.
//
//

#pragma mark once
#include "ofMain.h"

#define DIM_WIDTH 1920
#define DIM_HEIGHT 1080
#define LONG_WALL 3250
#define SHORT_WALL 2450
#define HEIGHT_WALL 750
#define TILE_SIZE 125
#define NUM_PANELS 70 //max 70
#define NUM_FRAMES 60

//animated grid, banner, Raven controller, face controller

enum updateType{
    AllFacesDelete,
    AllFacesPopulate,
    
    AllTransparentNow,
    AllOpaqueNow,
    RandomFadeIn,
    RandomFadeOut,
    AllTransparentFade,
    AllOpaqueFade,
    
    SwapFaces

    
};
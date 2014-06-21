//
//  ofScreen.h
//  relationGame
//
//  Created by Emrys on 6/20/14.
//
//  #ifndef relationGame_ofScreen_h
//  #define relationGame_ofScreen_h
//
//  #endif

#ifndef _OF_SCREEN
#define _OF_SCREEN

#include "ofMain.h"

class ofScreen {
    
public:
    
    // Public Methods
    void update();
    void draw();
    
    // Public Variables
    float x;      // position
    float y;
    float speedY; // speed and direction
    float speedX;
    int dim;      // size
    
    // Costructor
    ofScreen();
    
private:
    
};

#endif

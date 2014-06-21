//
//  ofCharacter.h
//  Matchmaker
//
//  Created by Emrys on 6/20/14.
//
//  #ifndef Matchmaker_ofCharacter_h
//  #define Matchmaker_ofCharacter_h
//
//  #endif

#ifndef _OF_CHARACTER
#define _OF_CHARACTER

#include "ofMain.h"

class ofCharacter {
    
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
    ofCharacter();
    
private:
    
};

#endif
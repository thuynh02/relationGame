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
    void update( int, int );
    void draw();
    
    // Public Variables
    float x;      // position
    float y;
    float width;  // dimensions
    float height;
    
    float speedY; // speed and direction
    float speedX;
    
    float range;
    int footSpace;
    ofImage charImage;

    // Constructor
    ofCharacter(    string imagePath,
                    float x = 0,
                    float y = 0,
                    float speedX = ofRandom(-1, 1),
                    float speedY = ofRandom(-1, 1)
                );
    
    // Destructor
    ~ofCharacter();
    
private:
    bool isWalking;
    unsigned long long startTime;
    unsigned long long targetTime;
    unsigned long long timeLeftInMilliseconds;
};

#endif
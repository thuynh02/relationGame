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

#define MAPWIDTH 64
#define MAPHEIGHT 96

#include "ofMain.h"

class ofCharacter {
    
public:
    
    // Public Methods
    void update( bool );
    void draw();
    
    void animateWalkLeft();
    void animateWalkRight();
    void animateWalkForward();
    void animateWalkBackward();
    bool timeToTransition();
    
    // Public Variables
    float x;      // position
    float y;
    int currentPos;
    int dirX, dirY;
    float imgX;  // dimensions    
    float speedY; // speed and direction
    float speedX;
    
    float range;
    int footSpace;
    ofRectangle footRect;
    ofRectangle rangeRect;
    
    int charIndex;
    ofImage charImage, baseImage, eyesImage, hairImage, shoesImage, topsImage, bottomsImage;
    ofColor charColor, eyesColor, hairColor, shoesColor, topsColor, bottomsColor;
    string name, introduction;
    
    void genColor( ofColor& );
    void endConvo();
    void startConvo( ofCharacter* );
    
    bool inConvo;
    bool isWalking;
    ofCharacter* convoPartner;
    
    // Constructor
    ofCharacter(    string name,
                    string introduction,
                    int charIndex,
                    string imagePath,
                    string basePath = "",
                    string eyesPath = "",
                    string hairPath = "",
                    string shoesPath = "",
                    string topsPath = "",
                    string bottomsPath = "",
                    float x = 0,
                    float y = 0,
                    float speedX = ofRandom(-1, 1),
                    float speedY = ofRandom(-1, 1)
                );
    
    // Destructor
    ~ofCharacter();
    
private:
    unsigned long long startTime;
    unsigned long long targetTime;
    unsigned long long timeLeftInMilliseconds;
    
};

#endif
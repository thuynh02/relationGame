//
//  ofScreen.h
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#ifndef _OF_MINIGAME
#define _OF_MINIGAME

#include "ofMain.h"
#include "ofLevelCheckpoints.h"
#include <sstream>

class ofMinigame {
    
public:
    
    // Public Methods
    void update();
    void draw();
    void resetSize( float, float );
    void loadLevel(int level, ofImage* spriteReference);
    void drawLevel();
    bool playMini( ofRectangle* mouse );
//    void drawTimer();
    
    // Public Variables
    float x;        // position
    float y;
    float width;
    float height;
    bool isActive;
    string gameType;
    int minutes, seconds;
    unsigned long long startTime;
    unsigned long long targetTime;
    unsigned long long timeLeftInMilliseconds;
    ofTrueTypeFont gameFont;
    int mazeProgress;
    int levelPosX;
    int levelPosY;
    ofImage levelImage;
    ofImage pointImage;
    ofLevelCheckpoints* checkpoints;
    
    // Constructors
    ofMinigame( string gameType, float x, float y, string imagePath, int targetMinutes );
    ofMinigame( string gameType, float x, float y, int targetMinutes );
    
    // Destructor
    ~ofMinigame();
private:
    ofImage screenImage;
    
};

#endif// Reset Size Method - In case Toggling of Full Screen

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
    void loadLevel(int level);
    void drawLevel();
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
    ofImage levelImage;
    ofLevelCheckpoints* checkpoints;
    
    // Constructors
    ofMinigame( string gameType, float x, float y, string imagePath, int targetMinutes );
    ofMinigame( string gameType, float x, float y, float width, float height, int targetMinutes );
    // Destructor
    ~ofMinigame();
private:
    ofImage screenImage;
    
};

#endif
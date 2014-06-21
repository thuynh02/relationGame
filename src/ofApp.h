#pragma once
#ifndef _0F_APP
#define _0F_APP

#include "ofMain.h"
#include "ofCharacter.h"
#include "ofMinigame.h"

#define MINIGAMETIME 3
#define FONTSIZE 32
#define NUMBEROFCHARACTERS 10

class ofApp : public ofBaseApp{

public:
    // Public Methods
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    enum ScreenType { START, CHARACTER, INSTRUCTIONS, PARTY, MINIGAME, PAUSE, ENDING };
    
private:
    ScreenType currentScreen, previousScreen;
    
    // Private Member Variables
    ofImage logo;
    ofImage screenBG;
    
    ofCharacter* player;
    
    int numOfCharacters;
    ofCharacter** characters; // Array of Characters
    
    ofMinigame* modeParty;
    
    char timerString[255];
    ofTrueTypeFont myFont;
    
    void mergeSortCharacters( ofCharacter** );

};

#endif
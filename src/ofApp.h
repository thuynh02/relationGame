#pragma once
#ifndef _0F_APP
#define _0F_APP

#include "ofMain.h"
#include "ofCharacter.h"
#include "ofMinigame.h"
#include "ofxTextSuite.h"
#include <sstream>

#define MINIGAMETIME 1
#define INSTRUCTLENGTH 7
#define NUMBEROFCHARACTERS 20

#define NUMTOPS 6
#define NUMBOTTOMS 3
#define NUMEYES 1
#define NUMHAIR 8
#define NUMSHOES 1

class ofApp : public ofBaseApp{

public:
    // Public Methods
    void setup();
    void update();
    void reset(std::ostringstream&);
    void resetFont();
    void draw();
    void quickSort( ofCharacter*[], int, int );
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    enum ScreenType { START, INSTRUCTIONS, PARTY, MINIGAME, PAUSE, ENDING };
    enum DialogueType { GOOD_MINI, MID_MINI, BAD_MINI, NAMES };
    
private:
    ScreenType currentScreen, previousScreen;
    
    // Private Member Variables
    ofImage logo;
    ofImage screenBG;
    
    ofCharacter* player;
    
    int numOfCharacters;
    vector<ofCharacter*> characters; // Array of Characters
    ofMinigame* modeParty;
    ofImage checkpointSprite;
    ofImage miniCursor;
    int trackX, trackY;
    
    char timerString[255];
    ofTrueTypeFont myFont;
    
    void mergeSortCharacters( ofCharacter** );
    
    ofxTextBlock        myText;
    TextBlockAlignment  alignment;
    
    float marginTop, lineSpacing;

    string getNumToStr( std::ostringstream&, int );
    
    bool nameFieldActive, introFieldActive;
    string nameInput, introInput;
    ofRectangle nameField;
    ofRectangle introField;
    
    vector<string> instructions;
    vector<string> introduction;
    vector<float> yPoses;

};

#endif
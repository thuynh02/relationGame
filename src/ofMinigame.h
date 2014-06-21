//
//  ofScreen.h
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#ifndef _OF_MINIGAME
#define _OF_MINIGAME

#include "ofMain.h"

class ofMinigame {
    
public:
    
    // Public Methods
    void update();
    void draw();
    void changeImage( string );
    
    // Public Variables
    ofImage screenImage;
    float x;        // position
    float y;
    float width;
    float height;
    
    // Constructors
    ofMinigame( string );
    
    // Destructor
    ~ofMinigame();
private:
    
};

#endif
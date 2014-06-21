//
//  ofCharacter.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#include "ofCharacter.h"

// Default Constructor - Used to create a character
ofCharacter::ofCharacter() {
    x = 0;      // give some random positioning
    y = 0;
    
    speedX = ofRandom(-1, 1);           // and random speed and direction
    speedY = ofRandom(-1, 1);
    
    dim = 20;
}





// Update Method - Used to refresh character's properties
void ofCharacter::update( int mouseX, int mouseY){
    x = mouseX;
    y = mouseY;
}





// Update Method - Used to refresh character's properties
void ofCharacter::draw(){
    // values for R, G, B
    ofSetColor(120,120,120);
    ofCircle(x, y, dim);
    
}
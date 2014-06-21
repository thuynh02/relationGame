//
//  ofMinigame.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//
//

#include "ofMinigame.h"

// Default Constructor - Used to create a screen
ofMinigame::ofMinigame( string imagePath ) {
    x = 0;
    y = 0;
    screenImage.loadImage( imagePath );
}




// Destructor - Screens Built on the Heap
ofMinigame::~ofMinigame(){
    
}





// Update Method - Used to refresh screen's properties
void ofMinigame::update(){

}





// Update Method - Used to refresh screen's properties
void ofMinigame::draw(){
    ofSetColor( 255, 255, 255 );
    screenImage.draw(x, y, ofGetWidth(), ofGetHeight());
}

// changeScreen Method - Used to change screen image
void ofMinigame::changeImage( string newPath ){
    ofSetColor( 255, 255, 255 );
    screenImage.loadImage( newPath );
}
//
//  ofCharacter.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#include "ofCharacter.h"
#define PROBTIME 5

// Default Constructor - Used to create a character
ofCharacter::ofCharacter( string imagePath, float x, float y, float speedX, float speedY )
    : x(x), y(y), speedX( speedX ), speedY( speedY ), range( ofRandom( 1, 5 ) ), isWalking( true )
{
    charImage.loadImage( imagePath );
    width = charImage.getWidth();
    height = charImage.getHeight();
    footSpace =charImage.getHeight() / 5;
    
    startTime = ofGetElapsedTimeMillis();

}





// Update Method - Used to refresh character's properties
void ofCharacter::update( int x, int y ){
    this->x = x;
    this->y = y;
}

void ofCharacter::update(){
    
    // Every PROBTIME seconds, check if it is time to alter between walking and standing
    if( ofGetElapsedTimeMillis() - startTime > PROBTIME * 1000 ){
        if( ofRandom( -1, 1 ) > 0 ) { isWalking = !isWalking; }
        startTime = ofGetElapsedTimeMillis();
    }
    
    if( isWalking ) {
        if( x < 0 ){
            x = 0;
            speedX *= ofRandom(-1.5, -0.5);
        } else if( x + width > ofGetWidth() ){
            x = ofGetWidth() - width;
            speedX *= ofRandom(-1.5, -0.5);
        }
        
        if( y < 0 ){
            y = 0;
            speedY *= ofRandom(-1.5, -0.5);
        } else if( y + height > ofGetHeight() ){
            y = ofGetHeight() - height;
            speedY *= ofRandom(-1.5, -0.5);
        }
        
        x += speedX;
        y += speedY;
    }
}




// Update Method - Used to refresh character's properties
void ofCharacter::draw(){
    ofSetColor( 120, 120, 120 );
    ofEllipse( x + width/2,
              y + height,
              range * (height) / 2,
              range * (height) / 4 );
    
    ofSetColor( 255, 255, 255 );
    charImage.draw(x, y, width, height);
    
    ofSetColor( 255, 255, 255, 100 );
    ofRect( x, y + height - footSpace, width, footSpace );
}
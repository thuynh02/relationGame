//
//  ofCharacter.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#include "ofCharacter.h"

// Default Constructor - Used to create a character
ofCharacter::ofCharacter( string imagePath, float x, float y, float speedX, float speedY )
    : x(x), y(y), speedX( speedX ), speedY( speedY )
{
    charImage.loadImage( imagePath );
    width = charImage.getWidth();
    height = charImage.getHeight();
    footSpace =charImage.getHeight() / 5;
}





// Update Method - Used to refresh character's properties
void ofCharacter::update( int x, int y ){
    this->x = x;
    this->y = y;
}





// Update Method - Used to refresh character's properties
void ofCharacter::draw(){
    ofSetColor( 255, 255, 255 );
    charImage.draw(x, y, width, height);
    ofSetColor( 120, 120, 120 );
    ofRect( x, y + height - footSpace, width, footSpace );
}
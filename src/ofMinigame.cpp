//
//  ofMinigame.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//
//

#include "ofMinigame.h"

// Default Constructor - Used to create a minigame
ofMinigame::ofMinigame( string gameType, float x, float y, float width, float height, int targetMinutes ) : x(x), y(y), width( width ), height( height ), isActive( true ), minutes( targetMinutes ), seconds( 0 )
{
    startTime = ofGetElapsedTimeMillis();
    targetTime = targetMinutes * 60000; // 1 minute = 60000 milliseconds
    timeLeftInMilliseconds = targetTime;
}

ofMinigame::ofMinigame( string gameType, float x, float y, string imagePath, int targetMinutes )
    : x(x), y(y), isActive( true ), minutes( targetMinutes ), seconds( 0 )
{
    screenImage.loadImage( imagePath );
    this->width = screenImage.getWidth();
    this->height = screenImage.getHeight();
    startTime = ofGetElapsedTimeMillis();
    targetTime = targetMinutes * 60000; // 1 minute = 60000 milliseconds
    timeLeftInMilliseconds = targetTime;
}




// Update Method - Used to refresh minigame's properties
void ofMinigame::update(){
    
    // If there is still time left
    if( timeLeftInMilliseconds > 0 ) {
        
        // Take the number of milliseconds from start time to the current time
        // Get the number of milliseconds equivalent to the number of minutes needed to pass
        // Subtract the first from the second to get the time remaining in milliseconds
        // Then divide that by 1000 ( 1 second = 1000 milliseconds ) to get time remaining in seconds
        timeLeftInMilliseconds = targetTime - ( ofGetElapsedTimeMillis() - startTime );
        minutes = ( timeLeftInMilliseconds / 1000 ) / 60;
        seconds = ( timeLeftInMilliseconds / 1000 ) % 60;
        
    }
    // End of the minigame
    else {
        isActive = false;
    }
}





// Draw Method - Used to draw the minigame
void ofMinigame::draw(){
    if( isActive ){
        ofSetColor( 0, 0, 0 );
        ofRect( x, y, width, height );
        // screenImage.draw(x, y, ofGetWidth(), ofGetHeight());
    }
}



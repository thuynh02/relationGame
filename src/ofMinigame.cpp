//
//  ofMinigame.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//
//

#include "ofMain.h"
#include "ofMinigame.h"





// Default Constructor - Used to create a minigame
ofMinigame::ofMinigame( string gameType, float x, float y, int targetMinutes ) :x(x), y(y), width( ofGetWidth() ), height( ofGetHeight() ), isActive( true ), minutes( targetMinutes ), seconds( 0 )
{
    startTime = ofGetElapsedTimeMillis();
    targetTime = targetMinutes * 60000; // 1 minute = 60000 milliseconds
    timeLeftInMilliseconds = targetTime;
    mazeProgress = 0;
    gameFont.loadFont("fonts/verdana.ttf", 16 );
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
    mazeProgress = 0;
    gameFont.loadFont("fonts/verdana.ttf", 16 );
}





ofMinigame::~ofMinigame(){}





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
    if( minutes == 0 && seconds == 0 ) { isActive = false; }
}





// Draw Method - Used to draw the minigame
void ofMinigame::draw(){
    if( isActive ){
//        screenImage.draw(x, y, ofGetWidth(), ofGetHeight());
    }
}




// Reset Size Method - In case Toggling of Full Screen
void ofMinigame::resetSize( float x, float y ){
    this->x = x;
    this->y = y;
    this->width = ofGetWidth();
    this->height = ofGetHeight();
};

void ofMinigame::loadLevel(int level, ofImage* spriteReference){
    std::ostringstream oss;
    oss << level;
    levelImage.loadImage("../../../data/levels/level" + oss.str() + ".png" );
    pointImage.loadImage("../../../data/general/checkpoint.png" );
    checkpoints = new ofLevelCheckpoints( level, "../../../data/levels/level" + oss.str() + ".txt" );
    
    levelPosX = (ofGetWidth()/2)-(levelImage.width/2);
    levelPosY = (ofGetHeight()/2)-(levelImage.height/2);
    for( size_t i = 0; i < checkpoints->listOfPoints.size(); ++i ){
        checkpoints->listOfPoints[i]->referToImage(spriteReference);
        checkpoints->listOfPoints[i]->boundary =
            new ofRectangle( levelPosX + checkpoints->listOfPoints[i]->x - pointImage.width/2,
                             levelPosY + checkpoints->listOfPoints[i]->y - pointImage.height/2,
                             spriteReference->width,
                             spriteReference->height);
    }
    mazeProgress = 0;
}




void ofMinigame::drawLevel(){
    levelImage.draw( levelPosX, levelPosY, levelImage.width, levelImage.height );
    
    ofCheckpoint* currentPoint;
    
    for( size_t i = 0; i < checkpoints->listOfPoints.size(); ++i ){
        currentPoint = checkpoints->listOfPoints[i];
        if( currentPoint->active ){
                 if( currentPoint->type == 'S' ){ ofSetColor( 190,255,190 ); }
            else if( currentPoint->type == 'F' ){ ofSetColor( 255,190,190 ); }
            else if( currentPoint->type == 'P' ){ ofSetColor( 190,190,255 ); }
            currentPoint->sprite->draw( *currentPoint->boundary );
        }
    }
}



bool ofMinigame::playMini( ofRectangle* mouse ){
    
    ofCheckpoint* nextPoint = checkpoints->listOfPoints[mazeProgress];
    if( nextPoint->type == 'S' ){
        std::string startString = "Head to the green~";
        gameFont.drawString("Head to the green~",
                            ofGetWidth()/2 - (gameFont.getLetterSpacing()*startString.length())/2,
                            ofGetHeight()/2 - (gameFont.getLineHeight()/2) );
    }
        if( mazeProgress < checkpoints->listOfPoints.size() ){
            if( mouse->intersects( *nextPoint->boundary ) ){
                nextPoint->active = false;
                mazeProgress++;
            }
            return true;
        }
    
    mazeProgress = 0;
    return false;
    
}






//
//  ofCharacter.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#include "ofCharacter.h"
#define WAITTIME 4
#define WALKTIME 10

// Default Constructor - Used to create a character
ofCharacter::ofCharacter( string name, int charIndex, string bodyPath, string basePath, string eyesPath, string hairPath, string shoesPath, string topsPath, string bottomsPath, float x, float y, float speedX, float speedY )
    : name(name), charIndex(charIndex), x(x), y(y), imgX(0), currentPos(4), dirX(0), dirY(0), speedX( speedX ), speedY( speedY ), range( ofRandom( 1, 5 ) ), isWalking( true ), inConvo(false), convoPartner(NULL)
{
    charImage.loadImage( bodyPath );
    baseImage.loadImage( basePath );
    eyesImage.loadImage( eyesPath );
    hairImage.loadImage( hairPath );
    shoesImage.loadImage( shoesPath );
    topsImage.loadImage( topsPath );
    bottomsImage.loadImage( bottomsPath );
    
    genColor( charColor, 139, 90, 153, 255, 222, 173 );
    genColor( eyesColor );
    genColor( hairColor );
    genColor( shoesColor );
    genColor( topsColor );
    genColor( bottomsColor );

    footSpace =charImage.getHeight() / 5;
    footRect = ofRectangle(x, y + MAPHEIGHT - footSpace, MAPWIDTH, footSpace );
    rangeRect = ofRectangle(x + MAPWIDTH/2,
                            y + MAPHEIGHT,
                            range * (MAPHEIGHT) / 2,
                            range * (MAPHEIGHT) / 4 );
    startTime = ofGetElapsedTimeMillis();

    introduction.push_back("");
    
}

void ofCharacter::setIntro( ofTrueTypeFont& myFont, string intro ){

    for( int i = 0; i < intro.size(); i++ ){
        if ( myFont.stringWidth( introduction[ introduction.size() - 1 ] ) < (ofGetWidth() / 15) * 13 ) {
            introduction[ introduction.size() - 1 ] += intro[i];
        }
        else if ( myFont.stringWidth( introduction[  introduction.size() - 1 ] ) >= (ofGetWidth() / 15) * 13 ) {
            introduction.push_back( "" );
            introduction[ introduction.size() - 1 ] += intro[i];
        }
    }
}

ofCharacter::~ofCharacter(){};

void ofCharacter::genColor( ofColor& var, int rL, int gL, int bL, int rU, int gU, int bU ){
    var.r = static_cast<int>( ofRandom( rL, rU ) );
    var.g = static_cast<int>( ofRandom( gL, gU ) );
    var.b = static_cast<int>( ofRandom( bL, bU ) );
}

// Update Method - Used to refresh character's properties

void ofCharacter::update( bool player){
    
    if ( player ){
        if( x < 0 ){ x = 0 ;}
        else if (x + MAPWIDTH > ofGetWidth() ) { x = ofGetWidth()- MAPWIDTH; }
        if( y < 0 ){ y = 0 ;}
        else if (y + MAPHEIGHT > ofGetHeight() ) { y = ofGetHeight() - MAPHEIGHT; }
        x += dirX * speedX;
        y += dirY * speedY;
    }
    else{
        
        if( isWalking && !inConvo ) {
            
            // Every PROBTIME seconds, check if it is time to alter between walking and standing
            if( ofGetElapsedTimeMillis() - startTime > WALKTIME * 1000 ){
                if( ofRandom( -1, 1 ) > 0 ) { isWalking = !isWalking; }
                startTime = ofGetElapsedTimeMillis();
            }
            
            if( x < 0 ){
                x = 0;
                speedX *= ofRandom(-1.5, -0.5);
            } else if( x + MAPWIDTH > ofGetWidth() ){
                x = ofGetWidth() - MAPWIDTH;
                speedX *= ofRandom(-1.5, -0.5);
            }
            
            if( y < 0 ){
                y = 0;
                speedY *= ofRandom(-1.5, -0.5);
            } else if( y + MAPHEIGHT > ofGetHeight() ){
                y =  ofGetHeight() - MAPHEIGHT;
                speedY *= ofRandom(-1.5, -0.5);
            }
            
            x += speedX;
            y += speedY;
            
            if( speedX > 0 ) { dirX = 1; }
            else if( speedX == 0 ) { dirX = 0; }
            else if( speedX < 0 ) { dirX = -1; }
            
            if( speedY > 0 ) { dirY = 1; }
            else if( speedY == 0 ) { dirY = 0; }
            else if( speedY < 0 ) { dirY = -1; }
        }
        else if (!isWalking && !inConvo ){
            // Every PROBTIME seconds, check if it is time to alter between walking and standing
            if( ofGetElapsedTimeMillis() - startTime > WAITTIME * 1000 ){
                if( ofRandom( -1, 1 ) > 0 ) { isWalking = !isWalking; }
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }
    
    if( isWalking ){
        // LEFT: X = -1, Y = 0
        if( dirX == -1 && ( abs(speedX) >= abs(speedY) ) ){
            animateWalkLeft();
        }
        // RIGHT: X = 1, Y = 0
        else if( dirX == 1 && ( abs(speedX) >= abs(speedY) ) ){
            animateWalkRight();
        }
        // UP: X = 0, Y = -1
        else if( dirY == -1 ){
            animateWalkBackward();
        }
        // DOWN: X = 0, Y = 1
        else if( dirY == 1 ){
            animateWalkForward();
        }
    }
    else{
        if( currentPos >= 0 && currentPos < 4 ){ currentPos = 0; }
        else if( currentPos >= 4 && currentPos < 8 ){ currentPos = 4; }
        else if( currentPos >= 8 && currentPos < 12){ currentPos = 8; }
        else if( currentPos >= 12 && currentPos <= 16 ){ currentPos = 12; }
    }
    
    footRect.setPosition(x, y + MAPHEIGHT - footSpace );
    
}


void ofCharacter::endConvo( ){
    inConvo = false;
    isWalking = true;
    convoPartner = NULL;
}

void ofCharacter::startConvo( ofCharacter* other ){
    inConvo = true;
    isWalking = false;
    convoPartner = other;
    if ( hasDiscovered < interests.size() ) {hasDiscovered++;}
}

void ofCharacter::setInterests( string s  ){
    interests.push_back( s );
}

bool ofCharacter::timeToTransition(){
    if( ofGetElapsedTimeMillis() - targetTime > 130-(10*(speedX+speedY)) ){
        targetTime = ofGetElapsedTimeMillis();
        return true;
    }
    return false;
}

void ofCharacter::animateWalkLeft(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 4 ) { currentPos = 0; }
    }
}

void ofCharacter::animateWalkForward(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 8 ) { currentPos = 4; }
    }
}

void ofCharacter::animateWalkRight(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 12 ) { currentPos = 8; }    }
}

void ofCharacter::animateWalkBackward(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 16 ) { currentPos = 12; }
    }
}

// Draw Method - Used to refresh character's properties
void ofCharacter::draw(){
    ofSetColor( 120, 120, 120, 100 );
    ofEllipse( x + MAPWIDTH/2,
              y + MAPHEIGHT,
              range * (MAPHEIGHT) / 2,
              range * (MAPHEIGHT) / 4 );
    
    ofSetColor( charColor );
    charImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( 255, 255, 255 );
    baseImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( eyesColor );
    eyesImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( shoesColor );
    shoesImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( bottomsColor );
    bottomsImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);

    ofSetColor( topsColor );
    topsImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( hairColor );
    hairImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( 255, 255, 255, 100 );
    ofRect(footRect.x, footRect.y, footRect.width, footRect.height );
    
}

void ofCharacter::drawProfile( float xPos, float yPos){
    
    ofSetColor( charColor );
    charImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( 255, 255, 255 );
    baseImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( eyesColor );
    eyesImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( shoesColor );
    shoesImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( bottomsColor );
    bottomsImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( topsColor );
    topsImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( hairColor );
    hairImage.drawSubsection( xPos, yPos, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
}
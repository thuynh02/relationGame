#include "ofApp.h"
#include <string>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableSmoothing();
    
    // Initialization of Objects on Heap
    player = new ofCharacter( "characters/player.jpg");
    modeParty = new ofMinigame( "PARTY",
                                ofGetWidth() / 8,        // x-Position
                                ofGetHeight() / 8,       // y-Position
                                (ofGetWidth() / 8) * 6,  // width
                                (ofGetHeight() / 8) * 6, // height
                                3                        // target time
    );
    
    // Loading Fonts
    myFont.loadFont("fonts/verdana.ttf", 32);
    
    // Loading Logo
    logo.loadImage( "gameLogo.jpg" );
    
    // Loading Screen
    screenBG.loadImage( "screens/startScreen.jpg" );
    
    // Set-Up of Screens
    currentScreen = START;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    modeParty->update();
    player->update(mouseX, mouseY);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw the Screen Background
    ofSetColor( 255, 255, 255 );
    screenBG.draw( 0, 0, ofGetWidth(), ofGetHeight() );
    
    // Currently In Start Screen - Displays only Logo and Prompt
    if( currentScreen == START ){
        ofSetColor( 255, 255, 255 );
        logo.draw( ofGetWidth()/2 - logo.getWidth()/2, ofGetHeight()/2 - logo.getHeight()/2, logo.getWidth(), logo.getHeight() );
    }
    
    // Currently in Instruction Screen
    else if( currentScreen == INSTRUCTIONS ){
        player->draw();
    }
    
    // Currently in Party Screen
    else if( currentScreen == PARTY ){
        modeParty->draw();
        player->draw();
        
        ofSetColor( 120, 120, 120 );
        
        // Draw Timer only in minutes and seconds
        sprintf(timerString, ( modeParty->seconds < 10 ) ? "%d:0%d" : "%d:%d", modeParty->minutes, modeParty->seconds);
        myFont.drawString(timerString, ofGetWidth()/2 - myFont.stringWidth( timerString )/2, 40);
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Conditional Statement for Toggling Fullscreen
    if ( key == OF_KEY_F1 ) { ofToggleFullscreen(); }
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START ){
        previousScreen = START;
        currentScreen = INSTRUCTIONS;
    }
    else if( currentScreen == INSTRUCTIONS ){
        previousScreen = INSTRUCTIONS;
        currentScreen = PARTY;
    }
    else if( currentScreen == PARTY ) {
        
        // Set previousScreen because it is possible to pause here
        previousScreen = PARTY;
        
        // Change currentScreen, based on key, to MINIGAME, PAUSE, ENDING
        if( key == ' ' ){ currentScreen = MINIGAME; }
        else if( key == OF_KEY_SHIFT ) { currentScreen = PAUSE; }
        else if ( key == OF_KEY_BACKSPACE ) { currentScreen = ENDING; }
        
    }
    else if( currentScreen == MINIGAME) {
        
        // Set previousScreen because it is possible to pause here
        previousScreen = MINIGAME;
        
        // Change currentScreen, based on key, to PARTY, PAUSE, ENDING
        if( key == ' ' ) { currentScreen = PARTY; }
        else if( key == OF_KEY_SHIFT ) { currentScreen = PAUSE; }
        else if ( key == OF_KEY_BACKSPACE ) { currentScreen = ENDING; }
        
    }
    else if( currentScreen == PAUSE ) {
        
        // Change currentScreen, based on key, to value of previousScreen
        // previousScreen's Possible Values: PARTY, MINIGAME, ENDING
        if( key == OF_KEY_SHIFT ) { currentScreen = previousScreen; }
        else if ( key == OF_KEY_BACKSPACE ) { currentScreen = ENDING; }
        
    }
    else if ( currentScreen == ENDING ) {
        
        // Set previousScreen because it is possible to pause here
        previousScreen = ENDING;
        
        // Change currentScreen, based on key, to START, PAUSE
        if( key == ' ' ) { currentScreen = START; }
        else if( key == OF_KEY_SHIFT ) { currentScreen = PAUSE; }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START ){ screenBG.loadImage( "screens/startScreen.jpg"); }
    else if( currentScreen == INSTRUCTIONS ){ screenBG.loadImage( "screens/instructScreen.jpg"); }
    else if( currentScreen == PARTY ) { screenBG.loadImage( "screens/partyScreen.jpg"); }
    else if( currentScreen == MINIGAME ) { screenBG.loadImage( "screens/minigameScreen.jpg"); }
    else if( currentScreen == PAUSE ) { screenBG.loadImage( "screens/pauseScreen.jpg"); }
    else if( currentScreen == ENDING ) { screenBG.loadImage( "screens/endScreen.jpg"); }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

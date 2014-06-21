#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableSmoothing();
    
    // Initialization of Objects on Heap
    character = new ofCharacter();
    
    // Loading Logo
    logo.loadImage( "gameLogo.jpg" );
    
    // Loading Screen
    screenBG.loadImage( "screens/startScreen.jpg" );
    
    // Set-Up of Screens
    currentScreen = START;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    character->update(mouseX, mouseY);
    
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
    } else if( currentScreen == INSTRUCTIONS ){
    // Currently in Instruction Screen
        character->draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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

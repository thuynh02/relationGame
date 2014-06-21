#include "ofApp.h"
#include <string>

//--------------------------------------------------------------
void ofApp::setup(){
    
    std::ostringstream oss;
    ofEnableSmoothing();
    
    // Initialization of Objects on Heap
    player = new ofCharacter( "characters/blankBody.png", "", "", "", "", "", "", 100, 100, 1.5, 1.5);
    
    modeParty = new ofMinigame(
       "PARTY",
        0,
        0,
        MINIGAMETIME             // target time
    );
    
    // Loading Fonts
    resetFont();
    myText.init("fonts/verdana.ttf", 80);
    
    myText.setText("You came to a party hoping to meet up with some close friends of yours. Unfortunately, they all bailed on you at the last minute. You're already at the party, but it's been ages since you last tried to make some new friends. Make the most of the night and find a new person to connect with before the party ends on a lonely note. \nFind someone interesting on the guest list and walk over to them using the W, A, S, D keys. Once you get close to someone you'll have a chance to introduce yourself and start a conversation with them. Conversations are navigated with your mouse, you'll be following the flow of conversation quite literally with your pointer. Stay within the shapes given to you as best you can and be careful! When meeting someone new you need to pay attention to what they say and respect their boundaries. Too many run ins with the conversation's walls or going too fast will make people not want anything to do with you. \nGood luck, and one last thing... how do you want to say hello to the people you meet tonight?" );
    
    //Initially wrap the text to the screen width
    myText.wrapTextX( 0 );
    myText.wrapTextArea( (ofGetWidth()/3)*2, ofGetHeight()/2 );
    
    // Loading Logo
    logo.loadImage( "gameLogo.jpg" );
    
    // Loading Screen
    screenBG.loadImage( "screens/startScreen.jpg" );
    
    // Set-Up of Screens
    currentScreen = START;
    
    // Set-Up of Party Mode
    numOfCharacters = NUMBEROFCHARACTERS;
    characters = new ofCharacter*[numOfCharacters];
    for ( int i = 0; i < numOfCharacters; i++ ) {
        
        characters[i] = new ofCharacter(
            "characters/blankBody.png",
            "characters/eyes/base.png",
            "characters/eyes/" + getRandNum( oss, NUMEYES ) + ".png",
            "characters/shoes/" + getRandNum( oss, NUMSHOES ) + ".png",
            "characters/bottoms/" + getRandNum( oss, NUMBOTTOMS ) + ".png",
            "characters/tops/" + getRandNum( oss, NUMTOPS ) + ".png",
            "characters/hair/" + getRandNum( oss, NUMHAIR ) + ".png",
            ofRandom( modeParty->x, modeParty->width ),
            ofRandom(   modeParty->y + ( modeParty->height * i ) / + numOfCharacters,
                        modeParty->y + ( modeParty->height * (i + 1) ) / + numOfCharacters
            )
        );
    }
    
    // Set-Up of Minigame (First level test)
    modeParty->loadLevel(1);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    modeParty->update();
    
    for ( int i = 0; i < numOfCharacters; i++ ) {
        characters[i]->update( false );
    }
    
    if( !modeParty->isActive && ( currentScreen == PARTY || currentScreen == MINIGAME ) ) {
        previousScreen = currentScreen;
        currentScreen = ENDING;
    }
    
    player->update( true );
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
        ofSetColor( 120, 120, 120 );
        myText.draw( 0, ofGetHeight() );
    }
    
    // Currently in Party Screen
    else if( currentScreen == PARTY ){
        modeParty->draw();
        
        for ( int i = 0; i < numOfCharacters; i++ ) {
            characters[i]->draw();
        }
        
        player->draw();
        
        ofSetColor( 120, 120, 120 );
        
        // Draw Timer only in minutes and seconds
        sprintf(timerString, ( modeParty->seconds < 10 ) ? "%d:0%d" : "%d:%d", modeParty->minutes, modeParty->seconds);
        myFont.drawString(timerString, modeParty->width/2 - myFont.stringWidth( timerString )/2, 40);
        
    }
    else if( currentScreen == MINIGAME ){
        
        ofSetColor( 120, 120, 120 );
        
        // Draw Timer only in minutes and seconds
        sprintf(timerString, ( modeParty->seconds < 10 ) ? "%d:0%d" : "%d:%d", modeParty->minutes, modeParty->seconds);
        myFont.drawString(timerString, ofGetWidth()/2 - myFont.stringWidth( timerString )/2, 40);
        
        modeParty->drawLevel();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Conditional Statement for Toggling Fullscreen
    if ( key == OF_KEY_F1 ) {
        ofToggleFullscreen();
    }
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START && key == ' ' ){
        previousScreen = START;
        currentScreen = INSTRUCTIONS;
    }
    else if( currentScreen == INSTRUCTIONS && key == ' ' ){
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
        
        if( key == 'w' ){
            player->dirY = -1;
            if( player-> currentPos > 15 || player-> currentPos < 12 ) player->currentPos = 12;
        }
        if( key == 'a' ){
            player->dirX = -1;
            if( player-> currentPos > 3 ) player->currentPos = 0;
        }
        if( key == 's' ){
            player->dirY = 1;
            if( player-> currentPos > 7 || player-> currentPos < 4 ) player->currentPos = 4;
        }
        if( key == 'd' ){
            player->dirX = 1;
            if( player-> currentPos > 11 || player-> currentPos < 8 ) player->currentPos = 8;
        }
        
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
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START ){ screenBG.loadImage( "screens/startScreen.jpg"); }
    else if( currentScreen == INSTRUCTIONS ){ screenBG.loadImage( "screens/instructScreen.jpg"); }
    else if( currentScreen == PARTY ) { screenBG.loadImage( "screens/partyScreen.jpg"); }
    else if( currentScreen == MINIGAME ) { screenBG.loadImage( "screens/minigameScreen.jpg"); }
    else if( currentScreen == PAUSE ) { screenBG.loadImage( "screens/pauseScreen.jpg"); }
    else if( currentScreen == ENDING ) { screenBG.loadImage( "screens/endScreen.jpg"); }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if( currentScreen == PARTY ) {
        
        if( key == 'w' ){
            player->dirY = 0;
        }
        if( key == 'a' ){
            player->dirX = 0;
        }
        if( key == 's' ){
            player->dirY = 0;
        }
        if( key == 'd' ){
            player->dirX = 0;
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if( currentScreen == MINIGAME ){
        
    }
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
    modeParty->resetSize( 0, 0 );

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::resetFont(){
    myFont.loadFont("fonts/verdana.ttf", 32 );
    marginTop = myFont.stringHeight( instructions[0] );
    lineSpacing = myFont.stringHeight( instructions[0] );
}

string ofApp::getRandNum( std::ostringstream& oss, int value ) {
    oss.str("");
    oss << ofRandom(1, value);
    return oss.str();
}
//--------------------------------------------------------------
//void ofApp::quickSort( ofCharacter*[] yCharacters, int i, int j)
//{
//    int middle;
//    if (yCharacters[i]->y < yCharacters[j]->y)
//        {
//            middle = partition(yCharacters, i, j);
//            quicksort(num, top, middle);   // sort first section
//            quicksort(num, middle+1, bottom);    // sort second section
//        }
//    return;
//}
//












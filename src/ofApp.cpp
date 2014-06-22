#include "ofApp.h"
#include <string>

//--------------------------------------------------------------
void ofApp::setup(){
    
    std::ostringstream oss;
    ofEnableSmoothing();
    
    reset( oss );
    nameFieldActive = true, introFieldActive = false;
    
    // Loading Fonts
    resetFont();
    myText.init("fonts/verdana.ttf", 80);
    
    nameInput = "";
    introInput = "";
    introduction.push_back("RULE 1");
    introduction.push_back("RULE 1");
    introduction.push_back("RULE 1");
    introduction.push_back("RULE 1");
    introduction.push_back("RULE 1");
    
    //Initially wrap the text to the screen width
    myText.wrapTextX( 0 );
    myText.wrapTextArea( (ofGetWidth()/3)*2, ofGetHeight()/2 );
    
    // Loading Logo
    logo.loadImage( "gameLogo.jpg" );
    
    // Loading Screen
    screenBG.loadImage( "screens/startScreen.jpg" );
    
    // Set-Up of Screens
    currentScreen = START;
    
    if(currentScreen == INSTRUCTIONS ) { ofShowCursor(); }
    else { ofHideCursor();}
}

//--------------------------------------------------------------
void ofApp::update(){
    
    modeParty->update();
    
    for ( int i = 0; i < numOfCharacters; i++ ) { 
        characters[i]->update( false );
    }
    
    // Reorder
//    ofSort(characters, my_compare);
    if( !modeParty->isActive && ( currentScreen == PARTY || currentScreen == MINIGAME ) ) {
        previousScreen = currentScreen;
        currentScreen = ENDING;
    }
    
    player->update( true );
    
    std::sort( characters.begin(), characters.end() );
    
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
        myText.draw( 500, ofGetHeight() );
        myFont.drawString("NAME: ", ofGetWidth()/15, ofGetHeight()/10);
        myFont.drawString("INSTRUCTIONS: ", ofGetWidth()/15, ofGetHeight()/10 + myFont.getLineHeight() );
        for (int i = 0; i < introduction.size(); i++ ) {
            myFont.drawString( introduction[i], ofGetWidth()/15, ofGetHeight()/10 + myFont.getLineHeight()*(i+2) );
        }
        myFont.drawString(nameInput, ofGetWidth()/15 + myFont.stringWidth("NAME: ") * 1.25, ofGetHeight()/10);
        myFont.drawString(introInput, ofGetWidth()/15, (ofGetHeight()/10) + myFont.getLineHeight()*(introduction.size()+2) );
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
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Conditional Statement for Toggling Fullscreen
    if ( key == OF_KEY_F1 ) {
        ofToggleFullscreen();
        myText.wrapTextArea( (ofGetWidth()/3)*2, ofGetHeight()/2 );
    }
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START && key == OF_KEY_TAB ){
        previousScreen = START;
        currentScreen = INSTRUCTIONS;
    }
    else if( currentScreen == INSTRUCTIONS ){
        
        if( nameInput != "" && introInput != "" && key == OF_KEY_RETURN ){
            previousScreen = INSTRUCTIONS;
            currentScreen = PARTY;
        }
        else if( nameFieldActive && !introFieldActive ){
            if( key == OF_KEY_TAB ){ nameFieldActive = false; introFieldActive = true; }
            else if( key == OF_KEY_BACKSPACE || key == OF_KEY_DEL ) { nameInput = nameInput.substr(0, nameInput.size() - 1); }
            else if ( nameInput.size() < 15 ) { nameInput += key; }
        }
        else if( !nameFieldActive && introFieldActive ){
            if( key == OF_KEY_TAB ){ nameFieldActive = true; introFieldActive = false; }
            else if( key == OF_KEY_BACKSPACE || key == OF_KEY_DEL ) { introInput = introInput.substr(0, introInput.size() - 1); }
            else if ( introInput.size() < 22 ) { introInput += key; }
        }
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
        if( key == ' ' ) {
            currentScreen = START;
            delete player;
            delete modeParty;
            vector<ofCharacter*>::iterator it = characters.begin();
            for(; it != characters.end();){
                delete *it;
                it = characters.erase(it);
            }
        }
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
    ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    if( !introFieldActive && x > nameField.x && y > nameField.y && x < nameField.x + nameField.width && y < nameField.y + nameField.height  ){
        nameFieldActive = !nameFieldActive;
    }
    else if( !nameFieldActive &&  x > introField.x && y > introField.y && x < introField.x + introField.width && y < introField.y + introField.height  ){
        introFieldActive = !introFieldActive;
    }

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
}

void ofApp::reset( std::ostringstream& oss ){
    // Initialization of Objects on Heap
    player = new ofCharacter( "characters/blankBody.png",
                             "characters/eyes/base.png",
                             "characters/eyes/" + getRandNum( oss, NUMEYES ) + ".png",
                             "characters/shoes/" + getRandNum( oss, NUMSHOES ) + ".png",
                             "characters/bottoms/" + getRandNum( oss, NUMBOTTOMS ) + ".png",
                             "characters/tops/" + getRandNum( oss, NUMTOPS ) + ".png",
                             "characters/hair/" + getRandNum( oss, NUMHAIR ) + ".png",
                             100, 100, 1.5, 1.5);
    
    modeParty = new ofMinigame(
                               "PARTY",
                               0,
                               0,
                               MINIGAMETIME             // target time
                               );

    // Set-Up of Party Mode
    numOfCharacters = NUMBEROFCHARACTERS;
    for ( int i = 0; i < numOfCharacters; i++ ) {
        
        characters.push_back( new ofCharacter(
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
                              )
             );
        
    }

}

string ofApp::getRandNum( std::ostringstream& oss, int value ) {
    oss.str("");
    oss << static_cast<int>( ofRandom(1, value) );
    return oss.str();
}
//--------------------------------------------------------------




#include "ofApp.h"
#include <string>
#include <fstream>

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
    
    //Initially wrap the text to the screen width
    myText.wrapTextX( 0 );
    myText.wrapTextArea( (ofGetWidth()/3)*2, ofGetHeight()/2 );
    
    // Loading Logo
    logo.loadImage( "gameLogo.jpg" );
    
    // Loading Screen
    screenBG.loadImage( "screens/startScreen.jpg" );
    
    // Set-Up of Screens
    currentScreen = START;
    instructions.push_back( "You came to a party hoping to meet up with some close friends of " );
    instructions.push_back( "yours. Unfortunately, they all bailed on you at the last minute." );
    instructions.push_back( "You're already at the party, but it's been ages since you last tried to ");
    instructions.push_back( "make some new friends. Make the most of the night and find new ");
    instructions.push_back( "people to connect with before the party ends on a lonely note.");
    instructions.push_back( "" );
    instructions.push_back( "- Walk over to someone using the W, A, S, D keys:" );
    instructions.push_back( "     this will start a conversation");
    instructions.push_back( "- Pay attention, stay alert, and navigate the shape of the conversation ");
    instructions.push_back( "     with your mouse.");
    instructions.push_back( "- Too many mistakes will drive a potential friend away! ");
    instructions.push_back( "" );
    instructions.push_back( "Good luck! How will you say hello? Keep it short and sweet." );
    instructions.push_back( "" );
    
    introduction.push_back( "" );
    
    // Set-Up of Party Mode
    numOfCharacters = NUMBEROFCHARACTERS;
        
    // Set-Up of Minigame (First level test)
    modeParty->loadLevel(1);
    
    if(currentScreen == INSTRUCTIONS ) { ofShowCursor(); }
    else { ofHideCursor();}
    
    // Fetching dialogue
    
    vector< vector<string> > textData;
    vector<string> goodMini, midMini, badMini, names;
    textData.push_back( goodMini );
    textData.push_back( midMini );
    textData.push_back( badMini );
    textData.push_back( names );
    
    
    
    std::ifstream ifs( "../../../data/general/dialogue.txt" );
    std::string delimiter = ":";
    size_t pos = 0;
    std::string token;
    
    if( ifs ){
        std::string line;
        while( getline( ifs, line ) ){
            if( (pos = line.find(delimiter)) != std::string::npos){
                token = line.substr( 0, pos );
                line.erase( 0, pos + delimiter.length() );
                     if ( token == "g" ){ textData[GOOD_MINI].push_back(line); }
                else if ( token == "m" ){ textData[MID_MINI].push_back(line); }
                else if ( token == "b" ){ textData[BAD_MINI].push_back(line); }
                else if ( token == "n" ){ textData[NAMES].push_back(line); }
            }
        }
        ifs.close();
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    modeParty->update();
    
    for ( int i = 0; i < numOfCharacters; i++ ) { 
        characters[i]->update( false );
    }
    
    
    player->update( true );
    
    // Reorder
    yPoses.clear();
    for( int i = 0; i < numOfCharacters; i++ ) {
        yPoses.push_back( characters[i]->y );
    }
    yPoses.push_back( player-> y );
    
    ofSort( yPoses );
    
    if( !modeParty->isActive && ( currentScreen == PARTY || currentScreen == MINIGAME ) ) {
        previousScreen = currentScreen;
        currentScreen = ENDING;
    }
    
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
        
        myFont.loadFont("fonts/verdana.ttf", 30 );
        myFont.drawString("NAME: ", ofGetWidth()/15, ofGetHeight()/10);
        myFont.drawString("INSTRUCTIONS: ", ofGetWidth()/15, ofGetHeight()/10 + myFont.getLineHeight() );
        
        
        myFont.loadFont("fonts/verdana.ttf", 18 );
        for (int i = 0; i < instructions.size(); i++ ) {
            myFont.drawString( instructions[i], ofGetWidth()/15, ofGetHeight()/10 + myFont.getLineHeight()*(i+3) );
        }
        
        myFont.loadFont("fonts/verdana.ttf", 30 );
        
        myFont.drawString(nameInput, ofGetWidth()/15 + myFont.stringWidth("NAME: ") * 1.25, ofGetHeight()/10);
        
        myFont.drawString( "HOW WILL YOU INTRODUCE YOURSELF?", (ofGetWidth()/15), ( ofGetHeight()/10 ) + myFont.getLineHeight()*(instructions.size() - 4));
        for (int i = 0; i < introduction.size(); i++ ) {
            myFont.drawString( introduction[i], (ofGetWidth()/15)*2, ( ofGetHeight()/10 ) + myFont.getLineHeight()*(instructions.size() - 4) + myFont.getLineHeight()*(i+1) );
        }
        
        // myFont.drawString(introInput, ofGetWidth()/15, (ofGetHeight()/10) + myFont.getLineHeight()*(instructions.size()-3) );
    }
    // Currently in Party Screen
    else if( currentScreen == PARTY ){
        modeParty->draw();
        
        for (int i = 0; i < yPoses.size(); i++ ){
            if( player->y == yPoses[i] ){ player->draw(); }
            else{
                for ( int j = 0; j < numOfCharacters; j++ ) {
                    if( characters[j]->y == yPoses[i] ){ characters[j]->draw(); }
                }
            }
        }
        
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
//    if ( key == OF_KEY_F1 ) {
//        ofToggleFullscreen();
//        myText.wrapTextArea( (ofGetWidth()/3)*2, ofGetHeight()/2 );
//    }
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START && key == OF_KEY_TAB ){
        previousScreen = START;
        currentScreen = INSTRUCTIONS;
    }
    else if( currentScreen == INSTRUCTIONS ){
        
        if( nameInput != "" && introduction[0] != "" && key == OF_KEY_RETURN ){
            previousScreen = INSTRUCTIONS;
            currentScreen = PARTY;
            player->name = nameInput;
            for( int i = 0; i < introduction.size(); i++ ){ player->introduction += introduction[i]; }
        }
        else if( nameFieldActive && !introFieldActive ){
            if( key == OF_KEY_TAB ){ nameFieldActive = false; introFieldActive = true; }
            else if( key == OF_KEY_BACKSPACE || key == OF_KEY_DEL ) { nameInput = nameInput.substr(0, nameInput.size() - 1); }
            else if ( nameInput.size() < 15 ) { nameInput += key; }
        }
        else if( !nameFieldActive && introFieldActive ){
            if( key == OF_KEY_TAB ){ nameFieldActive = true; introFieldActive = false; }
            else if( key == OF_KEY_BACKSPACE || key == OF_KEY_DEL ) {
                if( introduction[ introduction.size() - 1 ] != "" ) {
                    introduction[ introduction.size() - 1 ] = introduction[ introduction.size() - 1 ].substr(0, introduction[ introduction.size() - 1 ].size() - 1);
                }
                else{
                    introduction.pop_back();
                    introduction[ introduction.size() - 1 ] = introduction[ introduction.size() - 1 ].substr(0, introduction[ introduction.size() - 1 ].size() - 1);
                }
            }
            else if ( myFont.stringWidth( introduction[ introduction.size() - 1 ] ) < (ofGetWidth() / 15) * 11 ) {
                introduction[ introduction.size() - 1 ] += key;
            }
            else if ( myFont.stringWidth( introduction[ introduction.size() - 1 ] ) >= (ofGetWidth() / 15) * 11 ) {
                if( introduction.size() < 3 ) {
                    introduction.push_back( "" );
                    introduction[ introduction.size() - 1 ] += key;
                }
            }
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
            if( (player->currentPos >= 16 || player->currentPos < 12) && player->dirX == 0 ){
                player->currentPos = 12;
            }
        }
        if( key == 'a' ){
            player->dirX = -1;
            if( player->currentPos >= 4){
                player->currentPos = 0;
            }
        }
        if( key == 's' ){
            player->dirY = 1;
            if( (player->currentPos >= 8 || player->currentPos < 4) && player->dirX == 0 ){
                player->currentPos = 4;
            }
        }
        if( key == 'd' ){
            player->dirX = 1;
            if( (player->currentPos >= 12 || player->currentPos < 8) ){
                player->currentPos = 8;
            }
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
            player->currentPos = 12;
        }
        if( key == 'a' ){
            player->dirX = 0;
            player->currentPos = 0;
        }
        if( key == 's' ){
            player->dirY = 0;
            player->currentPos = 4;
        }
        if( key == 'd' ){
            player->dirX = 0;
            player->currentPos = 8;
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
    
}

void ofApp::reset( std::ostringstream& oss ){
    // Initialization of Objects on Heap
    player = new ofCharacter(
                             "",
                             "",
                             static_cast<int>( ofRandom(numOfCharacters ) ),
                             "characters/blankBody.png",
                             "characters/eyes/base.png",
                             "characters/eyes/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMEYES) ) ) + ".png",
                             "characters/shoes/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMSHOES) ) ) + ".png",
                             "characters/bottoms/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMBOTTOMS) ) ) + ".png",
                             "characters/tops/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMTOPS) ) ) + ".png",
                             "characters/hair/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMHAIR) ) ) + ".png",
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
                              getNumToStr( oss, i ),
                              getNumToStr( oss, i*5 ),
                              i,
                              "characters/blankBody.png",
                              "characters/eyes/base.png",
                              "characters/eyes/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMEYES) ) ) + ".png",
                              "characters/shoes/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMSHOES) ) ) + ".png",
                              "characters/bottoms/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMBOTTOMS) ) ) + ".png",
                              "characters/tops/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMTOPS) ) ) + ".png",
                              "characters/hair/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMHAIR) ) ) + ".png",
                              ofRandom( modeParty->x, modeParty->width ),
                              ofRandom(   modeParty->y + ( modeParty->height * i ) / + numOfCharacters,
                                       modeParty->y + ( modeParty->height * (i + 1) ) / + numOfCharacters
                                       )
                              )
             );
        
    }

}

string ofApp::getNumToStr( std::ostringstream& oss, int value ) {
    oss.str("");
    oss << static_cast<int>( value );
    return oss.str();
}
//--------------------------------------------------------------




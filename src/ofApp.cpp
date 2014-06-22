#include "ofApp.h"
#include <string>
#include <fstream>
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
    
    std::ostringstream oss;
    ofEnableSmoothing();
    
    // Fetching dialogue
    int textTypes = 12;
    textData.resize( textTypes );
    
    textData[GOOD_MINI] = goodMini;
    textData[MID_MINI] = midMini;
    textData[BAD_MINI] = badMini;
    textData[NAMES] = names;
    textData[PLACES] = places;
    textData[LIKES] = likes;
    textData[SHOWS] = shows;
    textData[GROUPS] = groups;
    textData[HOBBIES] = hobbies;
    textData[PAST] = pastAction;
    textData[INTROS] = intros;
    textData[INTERESTS] = interests;
    
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
                else if ( token == "@" ){ textData[PLACES].push_back(line); }
                else if ( token == "*" ){ textData[LIKES].push_back(line); }
                else if ( token == "&" ){ textData[SHOWS].push_back(line); }
                else if ( token == "`" ){ textData[GROUPS].push_back(line); }
                else if ( token == "+" ){ textData[INTERESTS].push_back(line); }
                else if ( token == "$" ){ textData[PAST].push_back(line); }
                else if ( token == "i" ){ textData[INTROS].push_back(line); }
                else if ( token == "^" ){ textData[INTERESTS].push_back(line); }
            }
        }
        ifs.close();
    }
    
    reset( oss );
    nameFieldActive = true, introFieldActive = false;
    
    // Loading Fonts
    resetFont();
    
    // Loading Logo
    // logo.loadImage( "gameLogo.jpg" );
    
    // Loading Screen
    screenBG.loadImage( "screens/logoandstart.jpg" );
    convoGrad.loadImage( "screens/gradient.png" );
    
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
    
    // Set-Up of Party Mode
    numOfCharacters = NUMBEROFCHARACTERS;
        
    // Set-Up of Minigame (First level test)
    miniCursor.loadImage("../../../data/general/checkpoint.png");
    mouseBoundary.setWidth(miniCursor.width/8);
    mouseBoundary.setHeight(miniCursor.height/8);
    dialogueDuration = 300;
    
    checkpointSprite.loadImage( "../../../data/general/checkpoint.png");
    modeParty->loadLevel(1, &checkpointSprite );
    playingMini = false;
    
    if(currentScreen == INSTRUCTIONS ) { ofShowCursor(); }
    else { ofHideCursor();}

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if( currentScreen == MENU || currentScreen == PARTY || currentScreen == MINIGAME ){
    
        modeParty->update();
        
        player->update( true );
        
        for ( int i = 0; i < numOfCharacters; i++ ) { 
            characters[i]->update( false );
        }
        
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
            if( currentScreen == ENDING ) { screenBG.loadImage( "screens/endbackground.jpg"); }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw the Screen Background
    ofSetColor( 255, 255, 255 );
    screenBG.draw( 0, 0, ofGetWidth(), ofGetHeight() );
    
    // Currently In Start Screen - Displays only Logo and Prompt
    if( currentScreen == START ){
//        ofSetColor( 255, 255, 255 );
//        logo.draw( ofGetWidth()/2 - logo.getWidth()/2, ofGetHeight()/2 - logo.getHeight()/2, logo.getWidth(), logo.getHeight() );
    }
    
    // Currently in Instruction Screen
    else if( currentScreen == INSTRUCTIONS ){
        ofSetColor( 0, 0, 0 );
        
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
        
    }
    // Currently in Party Screen
    else if( currentScreen == PARTY ){
//        modeParty->draw();
        
        for (int i = 0; i < yPoses.size(); i++ ){
            if( player->y == yPoses[i] ){ player->draw(); }
            else{
                for ( int j = 0; j < numOfCharacters; j++ ) {
                    if( characters[j]->y == yPoses[i] ){ characters[j]->draw(); }
                }
            }
        }
        
        if( player->inConvo ){
            ofSetColor(255, 255, 255);
            convoGrad.draw( 0, 0, ofGetWidth(), ofGetHeight());
            myFont.drawString(player->name, 0, ofGetHeight()/2 + myFont.stringHeight(player->name)/2 );
        }
        
        for ( int i = 0; i < numOfCharacters; i++ ) {
            if( !player->inConvo && player->footRect.intersects( characters[i]->footRect ) ){
                myFont.drawString(characters[i]->name, ofGetWidth() - myFont.stringWidth(characters[i]->name)*1.25, ofGetHeight() - myFont.stringHeight(characters[i]->name)/2 );
            }
        }
        
        ofSetColor( 0, 0, 0 );
        
        // Draw Timer only in minutes and seconds
        sprintf(timerString, ( modeParty->seconds < 10 ) ? "%d:0%d" : "%d:%d", modeParty->minutes, modeParty->seconds);
        myFont.drawString(timerString, modeParty->width/2 - myFont.stringWidth( timerString )/2, 40);
        
    }
    else if( currentScreen == MINIGAME ){
        
        ofSetColor( 0, 0, 0 );
        
        // Draw Timer only in minutes and seconds
        sprintf(timerString, ( modeParty->seconds < 10 ) ? "%d:0%d" : "%d:%d", modeParty->minutes, modeParty->seconds);
        myFont.drawString(timerString, ofGetWidth()/2 - myFont.stringWidth( timerString )/2, 40);
        
        modeParty->drawLevel();
        
        playingMini = modeParty->playMini( &mouseBoundary );
        ofSetColor( 255,255,255 );
        miniCursor.draw( mouseBoundary );
        
        if( playingMini != 'e' ){
            if( playingMini == 'S' || playingMini == 'P' || playingMini == 'F' ){
                if( ofGetElapsedTimeMillis() - dialogueDuration > 300 ){
                    currentDialogue = textData[GOOD_MINI][static_cast<int>(ofRandom(textData[GOOD_MINI].size()))];
                }
            }
            myFont.loadFont("fonts/verdana.ttf", 14 );
            myFont.drawString( currentDialogue, mouseBoundary.x - myFont.stringWidth(currentDialogue)/2,
                               mouseBoundary.y - 50 );
        }
        else{
            modeParty->loadLevel( static_cast<int>(ofRandom(1, MAX_LEVELS+1)), &checkpointSprite );
            currentScreen = PARTY;
        }
    }
    else if( currentScreen == MENU ){
        
        ofSetColor( 0, 0, 0 );
        
        int row = ( numOfCharacters % (ofGetHeight()/MAPHEIGHT));
        int col = ( numOfCharacters / row);
        
        for( int i = 0; i < numOfCharacters; i++ ){
            characters[i]->drawProfile( ( i % row ) * ( ofGetWidth() / row ), ( i % col ) * MAPHEIGHT );
            
            ofSetColor(255, 255, 255)
            ;            myFont.loadFont("fonts/verdana.ttf", 12 );
            myFont.drawString(characters[i]->name, ( i % row ) * ( ofGetWidth() / row ) + MAPWIDTH, (( i % col ) + 1 ) * (MAPHEIGHT) - (MAPHEIGHT*0.75));
            
            myFont.loadFont("fonts/verdana.ttf", 10 );
            for( int j = 0; j < characters[i]->interests.size(); j++ ){
                myFont.drawString(characters[i]->interests[j], ( i % row ) * ( ofGetWidth() / row ) + MAPWIDTH, (( i % col ) + 1 ) * (MAPHEIGHT) - (MAPHEIGHT*0.75) + myFont.getLineHeight()* ( j + 1 ) );
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START ){
        previousScreen = START;
        currentScreen = INSTRUCTIONS;
    }
    else if( currentScreen == INSTRUCTIONS ){
        
        if( nameInput != "" && introduction[0] != "" && key == OF_KEY_RETURN ){
            previousScreen = INSTRUCTIONS;
            currentScreen = PARTY;
            player->name = nameInput;
            for( int i = 0; i < introduction.size(); i++ ){ player->introduction += introduction[i];
            }
            introduction.clear();
        }
        else if( nameFieldActive && !introFieldActive ){
            if( key == OF_KEY_RETURN || key == OF_KEY_TAB ){ nameFieldActive = false; introFieldActive = true; }
            else if( key == OF_KEY_BACKSPACE || key == OF_KEY_DEL ) { nameInput = nameInput.substr(0, nameInput.size() - 1); }
            else if ( nameInput.size() < 15 ) { nameInput += key; }
        }
        else if( !nameFieldActive && introFieldActive ){
            if( key == OF_KEY_RETURN || key == OF_KEY_TAB ){ nameFieldActive = true; introFieldActive = false; }
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
        if( key == OF_KEY_RETURN ){ currentScreen = MINIGAME; }
        else if( key == OF_KEY_SHIFT ) { currentScreen = MENU; }
        else if ( key == OF_KEY_BACKSPACE ) {
            currentScreen = ENDING;
        }
        else if (key == ' ' ) {
            if ( player->inConvo ){
                player->convoPartner->endConvo();
                player->endConvo();
            }
            else{
                for ( int i = 0; i < numOfCharacters; i++ ) {
                    if( player->footRect.intersects( characters[i]->footRect ) ){
                        if( !characters[i]->inConvo ){
                            player->startConvo( characters[i]);
                            characters[i]->startConvo(player);
                        }
                    }
                }
            }
        
        }
        if (!player->inConvo ){
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
            if( key == 'i' ){
                std::string intro = textData[INTROS][ static_cast<int>( ofRandom(textData[INTROS].size()) ) ];
                std::string delimiter = "#@*&`+$";
                std::size_t prev = 0, pos;
                std::string token;
                
                while( (pos = intro.find_first_of(delimiter)) != std::string::npos){
                    token = intro.substr( pos, 1 );
                    intro.erase( pos, 1 );
                    if ( token == "@" ){
                        intro.insert(pos, textData[PLACES][static_cast<int>(ofRandom(textData[PLACES].size()))]);
                    }
                    else if ( token == "*" ){
                        intro.insert(pos, textData[LIKES][static_cast<int>(ofRandom(textData[LIKES].size()))]);
                    }
                    else if ( token == "&" ){
                        intro.insert(pos, textData[SHOWS][static_cast<int>(ofRandom(textData[SHOWS].size()))]);
                    }
                    else if ( token == "`" ){
                        intro.insert(pos, textData[GROUPS][static_cast<int>(ofRandom(textData[GROUPS].size()))]);
                    }
                    else if ( token == "+" ){
                        intro.insert(pos, textData[HOBBIES][static_cast<int>(ofRandom(textData[HOBBIES].size()))]);
                    }
                    else if ( token == "$" ){
                        intro.insert(pos, textData[PAST][static_cast<int>(ofRandom(textData[PAST].size()))]);
                    }
                    else if ( token == "#" ){ intro.erase( pos, 4 ); intro.insert( pos, "TEST7" ); }
                }
            }
        }
        
    }
    else if( currentScreen == MINIGAME) {
        
        // Set previousScreen because it is possible to pause here
        previousScreen = MINIGAME;
        
        // Change currentScreen, based on key, to PARTY, PAUSE, ENDING
        if( key == ' ' ) { currentScreen = PARTY; }
        else if( key == OF_KEY_SHIFT ) { currentScreen = MENU; }
        else if ( key == OF_KEY_BACKSPACE ) { currentScreen = ENDING; }
        
    }
    else if( currentScreen == MENU ) {
        
        // Change currentScreen, based on key, to value of previousScreen
        // previousScreen's Possible Values: PARTY, MINIGAME, ENDING
        if( key == OF_KEY_SHIFT ) { currentScreen = previousScreen; }
        else if ( key == OF_KEY_BACKSPACE ) { currentScreen = ENDING; }
        
    }
    else if ( currentScreen == ENDING ) {
        
        // Set previousScreen because it is possible to pause here
        previousScreen = ENDING;
        
        // Change currentScreen, based on key, to START, PAUSE
        if( key == OF_KEY_SHIFT ) { currentScreen = MENU; }
        else {
            currentScreen = START;
            delete player;
            delete modeParty;
            vector<ofCharacter*>::iterator it = characters.begin();
            for(; it != characters.end();){
                delete *it;
                it = characters.erase(it);
            }
            std::ostringstream oss;
            reset( oss );
        }
        
    }
    
    // Conditional Statements for Altering Screen
    if( currentScreen == START ){ screenBG.loadImage( "screens/logoandstart.jpg"); }
    else if( currentScreen == INSTRUCTIONS ){ screenBG.loadImage( "screens/nameinstructionbackground.jpg"); }
    else if( currentScreen == PARTY ) { screenBG.loadImage( "screens/gamebackground.jpg"); }
    else if( currentScreen == MINIGAME ) { screenBG.loadImage( "screens/minigamebackground.jpg"); }
    else if( currentScreen == MENU ) { screenBG.loadImage( "screens/nameinstructionbackground.jpg"); }
    else if( currentScreen == ENDING ) { screenBG.loadImage( "screens/endbackground.jpg"); }

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
    if( currentScreen == MINIGAME ){
        ofHideCursor();
        mouseBoundary.setX(x);
        mouseBoundary.setY(y);
    }
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
    nameInput = "";
    introduction.clear();
    introduction.push_back( "" );
    player = new ofCharacter(
                 "",
                 "",
                 1,
                 "characters/blankBody.png",
                 "characters/eyes/base.png",
                 "characters/eyes/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMEYES) ) ) + ".png",
                 "characters/shoes/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMSHOES) ) ) + ".png",
                 "characters/bottoms/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMBOTTOMS) ) ) + ".png",
                 "characters/tops/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMTOPS) ) ) + ".png",
                 "characters/hair/" + getNumToStr( oss, static_cast<int>( ofRandom(1, NUMHAIR) ) ) + ".png",
                 100, 100, 1.5, 1.5
                 );

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
                  textData[NAMES][ static_cast<int>( ofRandom( textData[NAMES].size() ) ) ],
                  getNumToStr( oss, i*5 ),
                  i+1,
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
        for( int j = 0; j < 5; j++ ) { characters[ characters.size() - 1 ]->setInterests( "TEST" ); }
    }

}

string ofApp::getNumToStr( std::ostringstream& oss, int value ) {
    oss.str("");
    oss << static_cast<int>( value );
    return oss.str();
}
//--------------------------------------------------------------










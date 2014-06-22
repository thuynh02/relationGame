//
//  checkpoint.h
//  relationGame
//
//  Created by Tony Huynh on 6/21/14.
//
//

#ifndef relationGame_checkpoint_h
#define relationGame_checkpoint_h

#include "ofMain.h"
#include <string>


class ofCheckpoint{
public:
    
    void referToImage( ofImage* imageRef );
    
    // Public variables
    int x;
    int y;
    char type;
    ofImage* sprite;
    ofRectangle* boundary;
    
    
    // Constructor
    ofCheckpoint( int newX, int newY, char newType );
    ofCheckpoint();
};

#endif

//
//  checkpoint.h
//  relationGame
//
//  Created by Tony Huynh on 6/21/14.
//
//

#ifndef relationGame_checkpoint_h
#define relationGame_checkpoint_h

class ofCheckpoint{
public:
    
    // Public variables
    int x;
    int y;
    char type;
    
    // Constructor
    ofCheckpoint( int newX, int newY, char newType );
    ofCheckpoint();
};

#endif

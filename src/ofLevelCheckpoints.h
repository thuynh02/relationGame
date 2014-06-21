//
//  ofLevelCheckpoints.h
//  relationGame
//
//  Created by Tony Huynh on 6/21/14.
//
//

#ifndef relationGame_ofLevelCheckpoints_h
#define relationGame_ofLevelCheckpoints_h

#include "ofCheckpoint.h"
#include <iostream>

class ofLevelCheckpoints{
public:
    
    // Public Variables
    int level;
    ofCheckpoint checkpoints[];
    
    // Constructor
    ofLevelCheckpoints( int currentLevel, std::string coordinatesFilePath );
    
};


#endif

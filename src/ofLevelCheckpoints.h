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
#include <vector>

class ofLevelCheckpoints{
public:
    
    // Public Variables
    int level;
    std::vector<ofCheckpoint*> listOfPoints;
    
    // Constructor
    ofLevelCheckpoints( int currentLevel, std::string coordinatesFilePath );
};


#endif

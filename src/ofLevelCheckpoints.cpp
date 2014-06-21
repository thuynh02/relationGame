//
//  ofLevelCheckpoints.cpp
//  relationGame
//
//  Created by Tony Huynh on 6/21/14.
//
//

#include "ofLevelCheckpoints.h"
#include <fstream>

// Constructor
ofLevelCheckpoints::ofLevelCheckpoints( int currentLevel, std::string coordinatesFilePath )
:level(currentLevel)
{
    std::ifstream ifs( coordinatesFilePath.c_str() );
    if( ifs ){
        std::string coordinates;
        while( getline( ifs, coordinates ) ){
            
        }
    }
}
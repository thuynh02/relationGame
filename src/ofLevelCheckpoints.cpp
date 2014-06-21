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
    
    /*
     std::string s = "scott>=tiger>=mushroom";
     std::string delimiter = ">=";
     
     size_t pos = 0;
     std::string token;
     while ((pos = s.find(delimiter)) != std::string::npos) {
     token = s.substr(0, pos);
     std::cout << token << std::endl;
     s.erase(0, pos + delimiter.length());
     }
     std::cout << s << std::endl;
    */
    
    std::ifstream ifs( coordinatesFilePath.c_str() );
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    
    size_t numOfVariables = 3;
    int x, y;
    char type;
    
    
    if( ifs ){
        std::string coordinates;
        while( getline( ifs, coordinates ) ){
            for( size_t i = 0; i < numOfVariables; ++i ){
                if( (pos = coordinates.find(delimiter)) != std::string::npos){
                    token = coordinates.substr( 0, pos );
                    coordinates.erase( 0, pos + delimiter.length() );
                    if ( i == 0 ){ x = std::atoi( token.c_str() ); }
                    else if( i == 1 ){ y = std::atoi( token.c_str() ); }
                    else{ type = *token.c_str(); }
                }
            }
            listOfPoints.push_back( new ofCheckpoint(x, y, type) );
        }
    }
}


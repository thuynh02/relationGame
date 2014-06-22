//
//  ofCheckpoint.cpp
//  relationGame
//
//  Created by Tony Huynh on 6/21/14.
//
//

#include "ofCheckpoint.h"

ofCheckpoint::ofCheckpoint( int newX, int newY, char newType )
:x( newX ), y( newY ), type( newType ) {}

void ofCheckpoint::referToImage(ofImage* imageRef){
    sprite = imageRef;
}
//
//  Map.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Map.h"

Map::Map()
: rows( 0 ),
columns( 0 )
{}

Map::~Map() {

}

void Map::addTile( Tile* tile ) {
    Node::addNode( tile );
    
    tiles.push_back( tile );
}

void Map::setup() {
    for ( int i = 0; i < tiles.size(); i++ ) {
        Mesh* mesh = tiles.at( i )->getMesh();
        
      //y
    //z ////////// +
        //
        //
        //
        // +
        float x = 0;
        float yOffset = 0; //width - columns
        float zOffset = 0; //height - rows
        
        //assuming normalized tiles (-1, +1)
        //mesh->setPosition( glm::vec3( x, ) );
    }
}


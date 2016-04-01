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
        //assuming normalized tiles (-1, +1)
        float yOffset = 1; //width - columns
        float zOffset = 1; //height - rows
        
        float tileWidth = 2;
        float tileHeight = 2;
        
        int actualColumn = 0;
        
        if( i % this->rows == 0 ) {
            
        }
        mesh->setPosition( glm::vec3( x,
                                     yOffset + tileWidth,
                                     zOffset + actualColumn) );
        
    }
}


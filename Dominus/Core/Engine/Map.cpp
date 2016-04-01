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
    int currentColumn = 0;
    for ( int i = 0; i < tiles.size(); i++ ) {
        Node* node = tiles.at( i );
      //x ->
    //z ////////// +
    //| //
        //
        //
        // +
        float y = 0;
        //assuming normalized tiles (-1, +1)
        float xOffset = 1; //width -> columns
        float zOffset = -1; //height -> rows
        
        float tileWidth = 2;
        float tileHeight = 2;
        
        int currentRow = i % this->rows;
        if( currentRow == 0 && i != 0) {
            currentColumn++;
        }
        
        glm::vec3 translation = glm::vec3( xOffset + ( currentColumn * tileWidth ),
                                           y,
                                           zOffset - ( currentRow * tileHeight ) );

        node->setModelMatrix( glm::translate( translation ) );
    }
}


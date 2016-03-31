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


//
//  MapBuilder.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MapBuilder.h"
#include "ObjLoader.h"

MapBuilder::MapBuilder() {

}

MapBuilder::~MapBuilder() {

}

Map* MapBuilder::build( MapLoader *mapLoader, TilesLoader *tilesLoader ) {
    Map* map = new Map;
    
    MapInfo* mapInfo = mapLoader->load();
    std::vector<std::string> tilesInfo = tilesLoader->load( mapInfo->tilesResource );
    
    for ( int i = 0 ; i < mapInfo->tilesKeys.size(); i++ ) {
        int tileKey = mapInfo->tilesKeys.at( i );
        Mesh* mesh = new Mesh( new ObjLoader );
        mesh->load( tilesInfo.at( tileKey ) );
        
        Tile* tile = new Tile;
        tile->key = tileKey;
        tile->setMesh( mesh );
        
        map->addTile( tile );
    }
    map->columns = mapInfo->width;
    map->rows = mapInfo->height;
    return map;
}
//
//  MapLoader.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 30/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MapLoader.h"
#include "LuaScript.h"

MapLoader::MapLoader( std::string mapResource )
: mapResource( mapResource )
{ }

MapLoader::~MapLoader() {

}

MapInfo* MapLoader::load( ) {
    MapInfo* mapInfo = new MapInfo;
    LuaScript script( mapResource );
    mapInfo->width = script.get<int>( "map.width" );
    mapInfo->height = script.get<int>( "map.height" );
    mapInfo->tilesResource = script.get<std::string>( "map.tiles" );
    mapInfo->tilesKeys = script.getIntVector( "map.map_layout" );
    return mapInfo;
}
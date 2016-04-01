//
//  TilesLoader.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "TilesLoader.h"
#include "LuaScript.h"

TilesLoader::TilesLoader()
: tilesResource( "" )
{}

TilesLoader::TilesLoader( std::string tilesResource )
: tilesResource( tilesResource )
{ }

TilesLoader::~TilesLoader() {

}

std::vector<std::string> TilesLoader::load( std::string tilesResource ) {
    this->tilesResource = tilesResource;
    return load();
}

std::vector<std::string> TilesLoader::load( ) {
    LuaScript script("tiles.lua");
    std::vector<std::string> tilesInfo;
    std::vector<std::string> codes = script.getTableKeys("tiles");
    
    for (std::string code : codes) {
        std::string tileResource = script.get<std::string>("tiles."+code+".obj");
        tilesInfo.push_back( tileResource );
    }
    return tilesInfo;
}
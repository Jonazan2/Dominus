//
//  MapBuilder.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MapBuilder_h
#define MapBuilder_h

#include "Map.h"
#include "MapLoader.h"
#include "TilesLoader.h"

class MapBuilder {
public:
    MapBuilder();
    ~MapBuilder();

    Map* build( MapLoader* mapLoader, TilesLoader* tilesLoader );
};

#endif /* MapBuilder_h */

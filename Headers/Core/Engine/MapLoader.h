//
//  MapLoader.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 30/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MapLoader_h
#define MapLoader_h

#include "MapInfo.h"

class MapLoader {
public:
    MapLoader( std::string );
    ~MapLoader();
    
    MapInfo* load( );
    std::string mapResource;
};

#endif /* MapLoader_h */

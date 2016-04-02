//
//  MapInfo.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MapInfo_h
#define MapInfo_h

#include <string>
#include <vector>

class MapInfo {
public:
    MapInfo()
    :width( 0 ), height( 0 ),
    tilesResource( "" ) {}
    ~MapInfo() {}
    
    int width;
    int height;
    std::string tilesResource;
    std::vector<int> tilesKeys;
};
#endif /* MapInfo_h */

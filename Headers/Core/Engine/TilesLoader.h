//
//  TilesLoader.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef TilesLoader_h
#define TilesLoader_h

#include <vector>
#include <string>

class TilesLoader {
public:
    TilesLoader( );
    TilesLoader( std::string );
    ~TilesLoader();
    
    std::vector<std::string> load( std::string tilesResource );
    std::vector<std::string> load( );
    std::string tilesResource;
};

#endif /* TilesLoader_h */

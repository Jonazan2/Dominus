//
//  Map.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <vector>
#include "Tile.h"

class Map : public Node {
public:
    Map();
    ~Map();
    
    void addTile( Tile* tile );
    
    int rows;
    int columns;
    std::vector<Tile*> tiles;
};

#endif /* Map_h */

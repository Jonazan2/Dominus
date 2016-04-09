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
    
    void addTile( std::shared_ptr<Tile> tile );
    void setup();
    
    int rows;
    int columns;
    std::vector<std::shared_ptr<Tile>> tiles;
};

#endif /* Map_h */

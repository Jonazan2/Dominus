//
//  Tile.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Tile_h
#define Tile_h

#include "Node.hpp"

class Tile : public Node {
public:
    Tile();
    ~Tile();
    
    int key;
};

#endif /* Tile_h */

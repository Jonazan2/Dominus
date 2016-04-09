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
    virtual ~Tile();
    
    void onUpdate( );
    void onRestore( Scene* scene );
    void onRender( Scene* scene );
    void onRenderChildrends( Scene* scene );
    void onPostRender( Scene* scene );
    
    int key;
};

#endif /* Tile_h */

//
//  MeshBuilder.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 3/5/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MeshBuilder_h
#define MeshBuilder_h

#include "ObjLoader.h"

class Mesh;
class MeshBuilder {
public:
    MeshBuilder();
    
    std::shared_ptr<Mesh> buildMesh( std::shared_ptr<ObjLoader> objParser );
    
};

#endif /* MeshBuilder_h */

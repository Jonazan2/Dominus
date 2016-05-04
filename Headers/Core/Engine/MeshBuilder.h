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
class Shape;
class MeshBuilder {
public:
    MeshBuilder();
    
    std::shared_ptr<Mesh> buildMesh( std::shared_ptr<ObjLoader> objParser );
    void mapValues( std::vector<std::vector<int>> vectorRow,
                                std::shared_ptr<ShapeInfo> shapeInfo,
                                std::shared_ptr<Shape> shape );
};

#endif /* MeshBuilder_h */

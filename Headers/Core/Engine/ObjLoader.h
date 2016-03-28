//
//  ObjLoader.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 28/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef ObjLoader_h
#define ObjLoader_h

#include "MeshLoader.h"

class ObjLoader : public MeshLoader {
public:
    ObjLoader();
    ~ObjLoader();
    
    void load( const std::string file,
               std::vector<glm::vec3>* vertices,
               std::vector<glm::vec2>* uvs,
               std::vector<glm::vec3>* normals );
    std::vector<std::string> split( const std::string,
                                    const char ) const;
private:
    int numTriangles;
};

#endif /* ObjLoader_h */

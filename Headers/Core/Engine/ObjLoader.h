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
#include "Mesh.hpp"
#include <climits>

class ObjLoader : public MeshLoader {
public:
    ObjLoader();
    ~ObjLoader();
    
    //std::shared_ptr<Mesh> load( const std::string );
    std::vector<std::string> split( const std::string,
                                    const char ) const;
    std::shared_ptr<Shape> loadShape( std::ifstream file );
    
    glm::vec3 loadVertex( std::string vertexLine );
    glm::vec2 loadUv( std::string uvLine );
    glm::vec3 loadNormal( std::string normalLine );
    std::vector<std::vector<int>> loadIndexLine( std::string indexLine );
    std::vector<int> loadIndex( std::string indexString );
    
    int V_KEY = 0;
    int VT_KEY = 1;
    int VN_KEY = 2;
};

#endif /* ObjLoader_h */

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

class ObjLoader : public MeshLoader {
public:
    ObjLoader();
    ~ObjLoader();
    
    std::shared_ptr<Mesh> load( const std::string );
    std::vector<std::string> split( const std::string,
                                    const char ) const;
    std::shared_ptr<Shape> loadShape( std::ifstream file );
    
    std::vector<glm::vec3> loadVertex( std::string vertexLine );
    std::vector<glm::vec2> loadUv( std::string uvLine );
    std::vector<glm::vec3> loadNormal( std::string normalLine );
    std::vector<int> loadIndex( std::string indexLine );
private:
    int numTriangles;
};

#endif /* ObjLoader_h */

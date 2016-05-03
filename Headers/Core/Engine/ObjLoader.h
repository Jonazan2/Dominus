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
#include "StringStream.h"
#include <climits>
#include <memory>

class ObjLoader : public MeshLoader {
public:
    ObjLoader(  );
    ~ObjLoader();
    
    std::shared_ptr<ObjInfo> load( const std::string );
    std::vector<std::string> split( const std::string,
                                    const char ) const;
    
    std::shared_ptr<Shape> loadShape( std::shared_ptr<StringStream> file );
    
    glm::vec3 loadVertex( std::istringstream* vertexLine );
    glm::vec2 loadUv( std::istringstream* uvLine );
    glm::vec3 loadNormal( std::istringstream* normalLine );
    std::string parseMaterialLib( std::istringstream* mtlibLine );
    std::string parseMaterialName( std::istringstream* materiallLine );
    std::vector<std::vector<int>> loadIndexLine( std::istringstream* indexLine );
    std::vector<int> loadIndex( std::string indexString );
    
    int V_KEY = 0;
    int VT_KEY = 1;
    int VN_KEY = 2;
    
};

#endif /* ObjLoader_h */

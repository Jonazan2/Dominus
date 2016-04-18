//
//  Shape.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 18/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

#include <vector>
#include <string>

#include <glm/glm.hpp>

class Shape {
public:
    Shape();
    ~Shape();
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    std::string material;
};

#endif /* Shape_h */

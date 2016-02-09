//
//  Node.hpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 9/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Node {
public:
    Node();
    ~Node();
    
    void setModelMatrix( const glm::mat4 modelMatrix );
    glm::mat4 getModelMatrix();
    void setMesh( Mesh* mesh );
    Mesh* getMesh();
    void rotate(  const glm::vec3 rotation );
private:
    glm::mat4 modelMatrix;
    Mesh* mesh;

};

#endif /* Node_hpp */

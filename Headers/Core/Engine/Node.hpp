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
#include "INode.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene;

class Node : public INode{
public:
    Node();
    Node( Mesh* mesh );
    ~Node();
    
    void onRestore( Scene* scene );
    void onRender( Scene* scene );
    void onRenderChildrends( Scene* scene );
    void onPostRender( Scene* scene );
    void addNode( INode* node );
    
    glm::mat4 * getModelMatrix();
    void setModelMatrix( glm::mat4 modelMatrix );
    glm::mat4 * getToWorldMatrix();
    
    void setMesh( Mesh* mesh );
    Mesh* getMesh();
    void rotate(  const glm::vec3 rotation );
    void translate( const glm::vec3 translation );
private:
    std::vector< INode * > childNodes;
    glm::mat4 modelMatrix;
    glm::mat4 toWorldMatrix;
    Mesh* mesh;

};

#endif /* Node_hpp */

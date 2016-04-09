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

class Node : public INode {
public:
    Node();
    Node( std::shared_ptr<Mesh> mesh );
    virtual ~Node();
    
    void onUpdate();
    void onRestore( Scene* scene );
    void onRender( Scene* scene );
    void onRenderChildrends( Scene* scene );
    void onPostRender( Scene* scene );
    void addNode( std::shared_ptr<INode> node );
    
    glm::mat4 * getModelMatrix();
    void setModelMatrix( glm::mat4 modelMatrix );
    glm::mat4 * getToWorldMatrix();
    
    void setMesh( std::shared_ptr<Mesh> mesh );
    std::shared_ptr<Mesh> getMesh();
    void rotate(  const glm::vec3 rotation );
    void translate( const glm::vec3 translation );
    
    int getID();
private:
    std::vector<std::shared_ptr<INode>> childNodes;
    glm::mat4 modelMatrix;
    glm::mat4 toWorldMatrix;
    std::shared_ptr<Mesh> mesh;
    int id;
};

#endif /* Node_hpp */

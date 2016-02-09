//
//  Node.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 9/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Node.hpp"

Node::Node()
            :   modelMatrix( glm::mat4( 1 ) ),
                mesh( nullptr ){

}

Node::~Node(){

}

void Node::setModelMatrix( const glm::mat4 modelMatrix ) {
    this->modelMatrix = modelMatrix;
}

glm::mat4 Node::getModelMatrix() {
    return modelMatrix;
}

void Node::setMesh( Mesh *mesh ) {
    this->mesh = mesh;
}

Mesh* Node::getMesh() {
    return mesh;
}

void Node::rotate( const glm::vec3 rotation ) {
    glm::mat4 rotationX = glm::rotate( rotation.x , glm::vec3( 1.0, 0.0, 0.0 ));
    glm::mat4 rotationY = glm::rotate( rotation.y , glm::vec3( 0.0, 1.0, 0.0 ));
    glm::mat4 rotationZ = glm::rotate( rotation.z , glm::vec3( 0.0, 0.0, 1.0 ));
    
    glm::mat4 total = rotationZ * rotationY * rotationX;
    modelMatrix = modelMatrix * total;
}
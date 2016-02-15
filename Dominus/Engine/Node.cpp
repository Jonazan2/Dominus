//
//  Node.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 9/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Node.hpp"
#include "Scene.h"

Node::Node()
            :   modelMatrix( glm::mat4( 1 ) ),
                mesh( nullptr ){

}

Node::~Node(){

}

void Node::onRestore( Scene* scene ) {
    scene->addToBatch( this );
    for ( INode* node : childNodes ) {
        node->onRestore( scene );
    }
}

void Node::onRender( Scene* scene ) {
    glm::mat4 parent = scene->popMatrix();
    modelMatrix = modelMatrix * parent;
    scene->pushMatrix( modelMatrix );
}

void Node::onRenderChildrends( Scene* scene ) {
    for ( INode * node :  childNodes ) {
        node->onRender( scene );
        node->onRenderChildrends( scene );
        node->onPostRender( scene );
    }
}

void Node::onPostRender( Scene* scene ) {
    scene->addToBatch( this );
}

glm::mat4 * Node::getModelMatrix() {
    return &modelMatrix;
}

void Node::setMesh( Mesh *mesh ) {
    this->mesh = mesh;
}

Mesh* Node::getMesh() {
    return mesh;
}

void Node::rotate( const glm::vec3 rotation ) {
    glm::mat4 rotationX = glm::rotate( rotation.x , glm::vec3( 1.0, 0.0, 0.0 ) );
    glm::mat4 rotationY = glm::rotate( rotation.y , glm::vec3( 0.0, 1.0, 0.0 ) );
    glm::mat4 rotationZ = glm::rotate( rotation.z , glm::vec3( 0.0, 0.0, 1.0 ) );
    
    glm::mat4 total = rotationZ * rotationY * rotationX;
    modelMatrix = modelMatrix * total;
}

void Node::translate( const glm::vec3 translation ) {
    glm::mat4 translationMatrix = glm::translate( translation );
    modelMatrix = modelMatrix * translationMatrix;
}
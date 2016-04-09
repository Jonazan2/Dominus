//
//  Node.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 9/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Node.hpp"
#include "Scene.h"
#include "glm/ext.hpp"

Node::Node()
: toWorldMatrix( glm::mat4( 1 ) ),
modelMatrix( glm::mat4( 1 ) ) {
    mesh = std::shared_ptr<Mesh>( new Mesh );
    id = Scene::generateID();
}

Node::Node( std::shared_ptr<Mesh> mesh )
: Node() {
    this->mesh = mesh;
}

Node::~Node(){
    std::cout << "Node" << id << "deleted" << std::endl;
}

int Node::getID() {
    return id;
}

void Node::addNode( std::shared_ptr<INode> node ) {
    childNodes.push_back( node );
}

void Node::onUpdate() {
    for ( std::shared_ptr<INode> node : childNodes ) {
        node->onUpdate();
    }
}

void Node::onRestore( Scene* scene ) {
    for ( std::shared_ptr<INode> node : childNodes ) {
        node->onRestore( scene );
    }
}

void Node::onRender( Scene* scene ) {
    glm::mat4 parent = scene->getStack()->top();
    toWorldMatrix = parent * modelMatrix;
    scene->pushMatrix( toWorldMatrix );
}

void Node::onRenderChildrends( Scene* scene ) {
    for ( std::shared_ptr<INode> node :  childNodes ) {
        node->onRender( scene );
        node->onRenderChildrends( scene );
        node->onPostRender( scene );
    }
}

void Node::onPostRender( Scene* scene ) {
    scene->getStack()->pop();
}

glm::mat4 * Node::getToWorldMatrix() {
    return &toWorldMatrix;
}

glm::mat4 * Node::getModelMatrix() {
    return &modelMatrix;
}

void Node::setMesh( std::shared_ptr<Mesh> mesh ) {
    this->mesh = mesh;
}

std::shared_ptr<Mesh> Node::getMesh() {
    return mesh;
}

void Node::setModelMatrix( glm::mat4 modelMatrix ) {
    this->modelMatrix = modelMatrix;
}

void Node::rotate( const glm::vec3 rotation ) {
    glm::mat4 rotationX = glm::rotate( rotation.x ,
                                       glm::vec3( 1.0, 0.0, 0.0 ) );
    glm::mat4 rotationY = glm::rotate( rotation.y ,
                                       glm::vec3( 0.0, 1.0, 0.0 ) );
    glm::mat4 rotationZ = glm::rotate( rotation.z ,
                                       glm::vec3( 0.0, 0.0, 1.0 ) );
    
    glm::mat4 total = rotationZ * rotationY * rotationX;
    modelMatrix = modelMatrix * total;
}

void Node::translate( const glm::vec3 translation ) {
    glm::mat4 translationMatrix = glm::translate( translation );
    modelMatrix = modelMatrix * translationMatrix;
}
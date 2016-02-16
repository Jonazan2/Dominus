//
//  RenderScene.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 15/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "RenderScene.h"

RenderScene::RenderScene() {

}

RenderScene::~RenderScene() {

}

void RenderScene::onSceneCreated( Scene* scene ) {
    //buffer data
    Mesh * momoMesh = new Mesh;
    momoMesh->loadObj( "momo.obj" );
    
    Mesh* jokerMesh = new Mesh;
    jokerMesh->loadObj( "joker.obj" );
    
    Mesh* cubeMesh = new Mesh;
    cubeMesh->loadObj( "cube.obj" );
    std::vector<Mesh*> meshes = std::vector<Mesh*> ();
    meshes.push_back( momoMesh );
    meshes.push_back( jokerMesh );
    meshes.push_back( cubeMesh );
    
    std::vector<glm::mat4> modelMatrix = std::vector<glm::mat4> ();
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(1,1,1));
    glm::mat4 rotationXMatrix = glm::rotate( 180.0f,
                                            glm::vec3( 1.0f, 0.0f, 0.0f ) );
    glm::mat4 translationMatrix = glm::translate( glm::vec3( 0.0, 2.5, 0.0 ) );
    modelMatrix.push_back( translationMatrix * rotationXMatrix * scaleMatrix );
    translationMatrix = glm::translate( glm::vec3 ( 0.0, 0.0, 0.0 ) );
    modelMatrix.push_back( translationMatrix * rotationXMatrix * scaleMatrix );
    translationMatrix = glm::translate( glm::vec3( 0.0, 0.0, 0.0 ) );
    modelMatrix.push_back( translationMatrix * rotationXMatrix * scaleMatrix );
    
    //populate scene
    Node* momoNode = new Node;
    Node* jokerNode = new Node;
    Node* cubeNode = new Node;
}
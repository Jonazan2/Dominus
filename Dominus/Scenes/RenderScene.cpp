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
    
    Mesh* momoHolder = new Mesh;
    momoHolder->loadObj( "cube.obj" );
    
    Mesh* jokerHolder = new Mesh;
    jokerHolder->loadObj( "cube.obj" );
    
    Mesh* plane = new Mesh;
    plane->loadObj( "cube.obj" );
    
    //populate scene
    Node* momoNode = new Node( momoMesh );
    Node* jokerNode = new Node( jokerMesh );
    
    Node* momoHolderNode = new Node( momoHolder );
    Node* jokerHolderNode = new Node( jokerHolder );
    Node* planeNode = new Node( plane );
    
    planeNode->setModelMatrix( glm::scale( glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
    
    momoHolderNode->setModelMatrix( glm::translate( glm::vec3( 5.0f, 1.0f, 0.0f ) ) );
    jokerHolderNode->setModelMatrix( glm::translate( glm::vec3( -5.0f, 1.0f, 1.0f ) ) );
    
    momoNode->setModelMatrix( glm::translate( glm::vec3( 5.0f, 2.0f, 0.0f ) ) *
                             glm::rotate( 90.0f , glm::vec3( 0.0f, 1.0f, 0.0f ) ) *
                             glm::rotate( -90.0f , glm::vec3( 1.0f, 0.0f, 0.0f ) ) *
                             glm::scale( glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
    jokerNode->setModelMatrix( glm::translate( glm::vec3( -5.0f, 1.0f, 1.0f ) ) );
    
    planeNode->addNode( momoHolderNode );
    planeNode->addNode( jokerHolderNode );
    
    momoHolderNode->addNode( momoNode );
    jokerHolderNode->addNode( jokerNode );
    
    scene->addNode( planeNode );
    scene->load();
}
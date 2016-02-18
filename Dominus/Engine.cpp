//
//  Engine.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 27/01/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Engine.h"

Engine::Engine() : running( true ){
    //scene = new Scene;
}

Engine::~Engine(){

}

void Engine::init() {
//    gameScene = new RenderScene;
//    gameScene->onSceneCreated( scene );
    renderer = new Renderer;
    renderer->init();
//    Mesh* cubeMesh = new Mesh;
//    cubeMesh->loadObj( "cube.obj" );
//    Node* cubeNode = new Node();
//    cubeNode->setMesh( cubeMesh );
//    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,-10),
//                                       glm::vec3(0,0,0),
//                                       glm::vec3(0.0f, 1.0f, 0.0f)
//                                       );
//    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 100.0f);
//    glm::vec3 lightPosition = glm::vec3( 0.0, 0.0, 0.0 );
//    
//    renderer->updateCamera( viewMatrix );
//    renderer->updateProjection( projectionMatrix );
//    renderer->updateLightSource(lightPosition);
//    nodes.push_back( cubeNode );
    renderer->loadMesh( nodes );
}

void Engine::processInput(){

}

void Engine::update(double delta){
    renderer->draw( nodes );
}

void Engine::render(){
    //scene->render();
}

bool Engine::isRunning(){
    return running;
}
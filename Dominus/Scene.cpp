//
//  Scene.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Scene.h"

Scene::Scene() {
    renderer = new Renderer;
    camera = new Camera();
    rootNode = new Node;
    projectionMatrix = glm::perspective( 0.78f, (float)640/480, 0.01f, 100.0f );
    lightPosition = glm::vec3( 0.0, 0.0, 0.0 );
    renderer->updateCamera( *camera->getViewMatrix() );
    renderer->updateLightSource( lightPosition );
    renderer->updateProjection( projectionMatrix );
    renderer->init();
}

Scene::~Scene() {

}

void Scene::load() {
    rootNode->onRestore( this );
    renderer->loadMesh( renderBatch );
    renderBatch.clear();
}

void Scene::addNode( INode *node ) {
    rootNode->addNode( node );
}

void Scene::render() {
    pushMatrix( glm::mat4( 1 ) );
    rootNode->onRender( this );
    rootNode->onRenderChildrends( this );
    rootNode->onPostRender( this );
    
    renderer->draw( renderBatch );
    renderBatch.clear();
    renderer->present();
}

void Scene::pushMatrix( glm::mat4 matrix ) {
    matrixStack.push( matrix );
}

glm::mat4 Scene::popMatrix() {
    glm::mat4 result = matrixStack.top();
    matrixStack.pop();
    return result;
}

void Scene::addToBatch( Node *node ) {
    renderBatch.push_back( node );
}
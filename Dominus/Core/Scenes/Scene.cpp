//
//  Scene.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Scene.h"

int Scene::currentID = 0;

Scene::Scene( Renderer* renderer )
: renderer( renderer ),
lightNode( nullptr ),
camera( nullptr ) {
    rootNode = new Node;
    windowLayout = new Layout;
    pushMatrix( glm::mat4( 1 ) );
}

Scene::~Scene() {

}

int Scene::generateID() {
    return currentID++;
}

void Scene::update( double delta ) {
    rootNode->onUpdate();
}

void Scene::setMapNode( Node *node ) {
    this->mapNode = node;
}

Camera* Scene::getCamera() {
    return camera;
}

void Scene::setLightNode( LightNode *lightNode ) {
    this->lightNode = lightNode;
    rootNode->addNode( lightNode );
}

void Scene::setCamera( Camera* camera ) {
    this->camera = camera;
    rootNode->addNode( camera );
}

void Scene::setSceneHUD( UIComponent * component ) {
    windowLayout->setWidth(640);
    windowLayout->setHeight(480);
    
    windowLayout->addComponent( std::shared_ptr<UIComponent>( component ) );
}

void Scene::loadUI() {
    windowLayout->render( renderer );
    renderer->loadUI();
}

void Scene::load( Node *node, int renderState ) {
    renderer->updateState( renderState );
    renderer->load( node );
}

void Scene::render( Node *node, int renderState ) {
    if( camera != nullptr ) {
        renderer->updateProjection( camera->projectionMatrix );
        renderer->updateViewMatrix( camera->viewMatrix );
    }
    if( lightNode != nullptr ) {
        renderer->updateLightSource( lightNode->position );
    }
    renderer->updateState( renderState );
    renderer->draw( node );
}

void Scene::addNode( INode *node ) {
    rootNode->addNode( node );
    node->onRestore( this );
}

void Scene::render() {
    if( camera != nullptr ){
        rootNode->onRender( this );
        rootNode->onRenderChildrends( this );
        rootNode->onPostRender( this );
    }
}

std::stack<glm::mat4> * Scene::getStack() {
    return &matrixStack;
}

void Scene::pushMatrix( glm::mat4 matrix ) {
    matrixStack.push( matrix );
}

glm::mat4 Scene::popMatrix() {
    glm::mat4 result = matrixStack.top();
    matrixStack.pop();
    return result;
}
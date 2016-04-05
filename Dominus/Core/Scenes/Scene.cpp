//
//  Scene.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Scene.h"

Scene::Scene( Renderer* renderer ) :
                                    renderer( renderer ),
                                    lightNode( nullptr ),
                                    camera( nullptr ) {
    rootNode = new Node;
    windowLayout = new Layout;
    pushMatrix( glm::mat4( 1 ) );
}

Scene::~Scene() {

}

void Scene::update( double delta ) {
    rootNode->onUpdate();
    if( camera != nullptr ) {
        renderer->updateProjection( camera->projectionMatrix );
        renderer->updateViewMatrix( camera->viewMatrix );
    }
    if( lightNode != nullptr ) {
        renderer->updateLightSource( lightNode->position );
    }
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
    //iterate graph and populate the batch
    windowLayout->render( renderer );
    //load batch in gpu memory
    renderer->loadUI();
}

void Scene::load() {
    //iterate the graph and populate the batch
    rootNode->onRestore( this );
    //load batch in gpu memory
    renderer->load( renderBatch );
    renderBatch.clear();
}

void Scene::addNode( INode *node ) {
    rootNode->addNode( node );
}

void Scene::render() {
    if( camera != nullptr ){
        rootNode->onRender( this );
        rootNode->onRenderChildrends( this );
        rootNode->onPostRender( this );
        
        renderer->draw( renderBatch );
        renderBatch.clear();
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

void Scene::addToBatch( Node *node ) {
    renderBatch.push_back( node );
}
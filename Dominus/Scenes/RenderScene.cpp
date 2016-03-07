//
//  RenderScene.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 15/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "RenderScene.h"
#include "Log.hpp"

RenderScene::RenderScene() {
    yaw = -90.0f;
    pitch = 0;
}

RenderScene::~RenderScene() {

}

void RenderScene::onSceneCreated( Scene* scene ) {
    this->scene = scene;
    //buffer data
    Mesh * momoMesh = new Mesh;
    momoMesh->loadObj( "momo.obj" );
    momoMesh->setTexture( "diffuse.png" );
    
    Mesh* jokerMesh = new Mesh;
    jokerMesh->loadObj( "capsule.obj" );
    jokerMesh->setTexture( "capsule.png" );
    
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
    
    momoHolderNode->setModelMatrix( glm::translate( glm::vec3( 5.0f, 1.0f, 0.0f ) ) );
    jokerHolderNode->setModelMatrix( glm::translate( glm::vec3( -5.0f, 1.0f, 1.0f ) ) );
    
    momoNode->setModelMatrix( glm::translate( glm::vec3( 0.0f, 2.0f, 0.0f ) ) *
                             glm::rotate( -360.0f , glm::vec3( 1.0f, 0.0f, 0.0f ) ) *
                             glm::scale( glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
    
    jokerNode->setModelMatrix( glm::translate( glm::vec3( 0.0f, 2.0f, 0.0f ) ) *
                              glm::rotate( -360.0f , glm::vec3( 1.0f, 0.0f, 0.0f ) ));
    
    planeNode->addNode( momoHolderNode );
    planeNode->addNode( jokerHolderNode );
    
    momoHolderNode->addNode( momoNode );
    jokerHolderNode->addNode( jokerNode );
    
    scene->addNode( planeNode );
    scene->load();
}

void RenderScene::onUpdate( double delta ) {
    this->delta = delta;
}

void RenderScene::onKeyDown( Event* event ) {
    // Camera controls
    GLfloat cameraSpeed = 0.01f * delta;
    Camera* camera = scene->getCamera();
    switch ( event->keyCode ) {
        case GLFW_KEY_UP:
            camera->position += cameraSpeed * camera->front;
            break;
        case GLFW_KEY_DOWN:
            camera->position -= cameraSpeed * camera->front;
            break;
        case GLFW_KEY_LEFT:
            camera->position -= glm::normalize(glm::cross(
                                                          camera->front,
                                                          camera->up)) * cameraSpeed;
            break;
        case GLFW_KEY_RIGHT:
            camera->position += glm::normalize(glm::cross(
                                                          camera->front,
                                                          camera->up)) * cameraSpeed;
            break;
        default:
            break;
    }
    camera->update();
}

void RenderScene::onMouseDragged( double xRel, double yRel ) {
    GLfloat sensitivity = 0.01;
    double xoffset = xRel * sensitivity;
    double yoffset = yRel * sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    std::cout << yaw << std::endl;
    std::cout << pitch << std::endl;
    
    glm::vec3 front = scene->getCamera()->front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    scene->getCamera()->front = glm::normalize(front);
    scene->getCamera()->update();
}

void RenderScene::onCosumeInput( std::vector<Event *>* events ) {
    for ( int i = 0; i < events->size(); i++ ) {
        Event* event = events->at( i );
        if ( event->type == ON_RIGHT_CLICK_PRESS ) {
            event->consumed = true;
        } else if ( event->type == ON_LEFT_CLICK_RELEASE ) {
            event->consumed = true;
        } else if ( event->type == ON_KEY_PRESS ) {
            event->consumed = true;
        } else if ( event->type == ON_KEY_RELEASE ) {
            event->consumed = true;
        }
    }
}
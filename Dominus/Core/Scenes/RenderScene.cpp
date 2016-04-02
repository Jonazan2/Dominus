//
//  RenderScene.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 15/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "RenderScene.h"
#include "Log.hpp"
#include "HorizontalLayout.h"
#include "VerticalLayout.h"
#include "Button.h"
#include "PngTextureLoader.h"
#include "GLGpuTexture.h"
#include "ObjLoader.h"
#include "MapBuilder.h"

RenderScene::RenderScene() {
    upPressed = false;
    downPressed = false;
    leftPressed = false;
    rightPressed = false;
    
    rightClickPressed = false;
}

RenderScene::~RenderScene() {

}

void RenderScene::onSceneCreated( Scene* scene ) {
    populateScene( scene );
    populateUI( scene );
}

void RenderScene::populateScene( Scene* scene ) {
    this->scene = scene;
    //Camera setup
    Camera* camera = new Camera;
    camera->yaw = -45.0;
    camera->pitch = -25.0;
    camera->position = glm::vec3( -6.33f, 7.28f, 5.93f );
    scene->setCamera( camera );
    
    LightNode* lightNode = new LightNode;
    scene->setLightNode( lightNode );
    //buffer data
    Mesh * momoMesh = new Mesh( new ObjLoader );
    momoMesh->load( "momo.obj" );
    Texture* momoTexture = new Texture( new GLGpuTexture, new PngTextureLoader );
    momoTexture->load( "diffuse.png" );
    momoMesh->setTexture( momoTexture );
    
    Mesh* jokerMesh = new Mesh( new ObjLoader );
    jokerMesh->load( "capsule.obj" );
    Texture* jokerTexture = new Texture( new GLGpuTexture, new PngTextureLoader );
    jokerTexture->load( "capsule.png" );
    //TODO: png format issues loading capsule.png
    //jokerMesh->setTexture( jokerTexture );
    
    Mesh* momoHolder = new Mesh( new ObjLoader );
    momoHolder->load( "cube.obj" );
    
    Mesh* jokerHolder = new Mesh( new ObjLoader );
    jokerHolder->load( "cube.obj" );
    
    Mesh* plane = new Mesh( new ObjLoader );
    plane->load( "cube.obj" );
    
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

    MapBuilder* mapBuilder = new MapBuilder;
    Map* map = mapBuilder->build( new MapLoader( "map.lua" ) ,
                                  new TilesLoader( ) );
    map->setup();
    
    map->setModelMatrix( glm::scale( glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
    scene->addNode( map );
    scene->load();
}

void RenderScene::populateUI( Scene* scene ) {
    HorizontalLayout* root = new HorizontalLayout;
    Params params = Params();
    params.disposition = WEIGHT_DISPOSITION;
    root->setParams(params);
    Button* button = new Button;
    button->weight = 1;
    Button* button2 = new Button;
    button2->weight = 1;
    Texture* buttonTexture = new Texture( new GLGpuTexture, new PngTextureLoader );
    Texture* button2Texture = new Texture( new GLGpuTexture, new PngTextureLoader );
    buttonTexture->load( "button.png" );
    button2Texture->load( "button.png" );
    Params buttonParams = Params();
    buttonParams.width = WRAP;
    buttonParams.height = WRAP;
    buttonParams.gravity = DOWN;
    
    button2->setParams(buttonParams);
    button->setParams(buttonParams);
    button2->setTexture(button2Texture);
    button->setTexture( buttonTexture );
    
    scene->setSceneHUD( root );
    root->addComponent(button);
    root->addComponent(button2);
    scene->loadUI();
}

void RenderScene::onUpdate( double delta ) {
    GLfloat cameraSpeed = 0.01f * delta;
    Camera* camera = scene->getCamera();
    if( upPressed ) {
        camera->position += cameraSpeed * camera->front;
    }
    if( downPressed ){
        camera->position -= cameraSpeed * camera->front;
    }
    if( leftPressed ) {
        camera->position -= glm::normalize(glm::cross(
                                                      camera->front,
                                                      camera->up)) * cameraSpeed;
    }
    if( rightPressed ) {
        camera->position += glm::normalize(glm::cross(
                                                      camera->front,
                                                      camera->up)) * cameraSpeed;
    }
}

void RenderScene::onKeyDown( Event* event ) {
    switch ( event->keyCode ) {
        case GLFW_KEY_UP:
            if ( event->type == ON_KEY_PRESS ) {
                upPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                upPressed = false;
            }
            break;
        case GLFW_KEY_DOWN:
            if ( event->type == ON_KEY_PRESS ) {
                downPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                downPressed = false;
            }
            break;
        case GLFW_KEY_LEFT:
            if ( event->type == ON_KEY_PRESS ) {
                leftPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                leftPressed = false;
            }
            break;
        case GLFW_KEY_RIGHT:
            if ( event->type == ON_KEY_PRESS ) {
                rightPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                rightPressed = false;
            }
            break;
        default:
            break;
    }
    
}

void RenderScene::onMouseDragged( double xRel, double yRel ) {
    GLfloat sensitivity = 0.01;
    double xoffset = xRel * sensitivity;
    double yoffset = yRel * sensitivity;
    
    scene->getCamera()->yaw += xoffset;
    scene->getCamera()->pitch += yoffset;
}

void RenderScene::onCosumeInput( std::vector<Event *>* events ) {
    for ( int i = 0; i < events->size(); i++ ) {
        Event* event = events->at( i );
        if ( event->type == ON_RIGHT_CLICK_PRESS ) {
            event->consumed = true;
            xSaved = event->x;
            ySaved = event->y;
            rightClickPressed = true;
        } else if ( event->type == ON_RIGHT_CLICK_RELEASE ) {
            event->consumed = true;
            xSaved = 0;
            ySaved = 0;
            rightClickPressed = false;
        } else if ( event->type == ON_KEY_PRESS ) {
            event->consumed = true;
            onKeyDown( event );
        } else if ( event->type == ON_KEY_RELEASE ) {
            event->consumed = true;
            onKeyDown( event );
        } else if ( event->type == ON_MOUSE_MOVED ) {
            event->consumed = true;
            if ( rightClickPressed ) {
                onMouseDragged( event->x - xSaved, ySaved - event->y );
            }
        }
    }
}
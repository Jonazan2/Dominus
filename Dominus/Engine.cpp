 //
//  Engine.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 27/01/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Engine.h"
#include "GLFWInputHandler.h"

Engine::Engine() : running( true ){

}

Engine::~Engine(){

}

void Engine::init() {
    window = new Window( 640, 480 );
    window->initWindow();
    inputHandler = new GLFWInputHandler( window->windowHandler() );
    inputHandler->init();
    renderer = new Renderer( window->windowHandler() );
    scene = new Scene( renderer );
    gameScene = new RenderScene;
    gameScene->onSceneCreated( scene );
}

void Engine::processInput(){
    Event* event = inputHandler->poolEvent();
    switch ( event->type ) {
        case ON_WINDOW_CLOSED:
            running = false;
            break;
        case ON_MOUSE_DRAG:
            gameScene->onMouseDragged( event->xRelative,
                                       event->yRelative );
            break;
        case ON_CLICK_DOWN:
            gameScene->onMouseClicked( event->x, event->y );
            break;
        case ON_CLICK_RELEASE:
            gameScene->onMouseReleased( event->x, event->y );
            break;
        case ON_KEY_EVENT:
            gameScene->onKeyDown( event->key );
            break;
        default:
            break;
    }
}

void Engine::update( double delta ){
    gameScene->onUpdate( delta );
    scene->update( delta );
}

void Engine::render(){
    scene->render();
}

bool Engine::isRunning(){
    return running;
}
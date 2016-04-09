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
    renderer->init();
    
    scene = new Scene( renderer );
    
    gameScene = new RenderScene;
    gameScene->onSceneCreated( scene );
}

void Engine::processInput(){
    std::vector<std::shared_ptr<Event>> *events = inputHandler->poolEvents();
    consumeEvents( events );
    gameScene->onCosumeInput( events );
    events->clear();
}

void Engine::consumeEvents( std::vector<std::shared_ptr<Event>>* events ) {
    for ( int i = 0; i < events->size(); i++ ) {
        std::shared_ptr<Event> event = events->at( i );
        if( event->type == ON_WINDOW_CLOSED ) {
            running = false;
            event->consumed = true;
        }
    }
}

void Engine::update( double delta ){
    gameScene->onUpdate( delta );
    scene->update( delta );
}

void Engine::render(){
    renderer->clear();
    scene->render();
    renderer->drawUI();
    renderer->present();
}

bool Engine::isRunning(){
    return running;
}
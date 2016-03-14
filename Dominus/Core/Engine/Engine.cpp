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
    renderer->initUI();
    
    UIComponent* uiComponent = new UIComponent;
    Texture* texture = new Texture("diffuse.png");
    uiComponent->setTexture( texture );
    uiComponents.push_back( uiComponent );
    renderer->loadUI( uiComponents );
}

void Engine::processInput(){
    std::vector<Event*> * events = inputHandler->poolEvents();
    consumeEvents( events );
    gameScene->onCosumeInput( events );
    events->clear();
}

void Engine::consumeEvents( std::vector<Event *> * events) {
    for ( int i = 0; i < events->size(); i++ ) {
        Event* event = events->at( i );
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
    scene->render();
    renderer->drawUI( uiComponents );
}

bool Engine::isRunning(){
    return running;
}
//
//  Engine.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 27/01/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "Engine.h"

Engine::Engine() : running( true ){
    scene = new Scene;
}

Engine::~Engine(){

}

void Engine::init() {
    gameScene = new RenderScene;
    gameScene->onSceneCreated( scene );
}

void Engine::processInput(){
    // update other events like input handling
    glfwPollEvents ();
}

void Engine::update(double delta){

}

void Engine::render(){
    scene->render();
}

bool Engine::isRunning(){
    return running;
}
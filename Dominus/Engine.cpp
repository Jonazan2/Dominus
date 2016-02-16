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
    gameScene = new GameScene;
}

Engine::~Engine(){

}

void Engine::init() {
    gameScene->onSceneCreated( scene );
}

void Engine::processInput(){

}

void Engine::update(double delta){

}

void Engine::render(){
    scene->render();
}

bool Engine::isRunning(){
    return running;
}
//
//  Engine.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 27/01/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef __Dominus__Engine__
#define __Dominus__Engine__

#include "RenderScene.h"
#include "InputHandler.h"
#include "Window.h"

class Engine {
public:
    Engine();
    ~Engine();
    
    void init();
    void processInput();
    void update( double delta );
    void render();
    
    void consumeEvents( std::vector< std::shared_ptr< Event > > );
    
    bool isRunning();
private:
    bool running;
    Scene* scene;
    GameScene* gameScene;
    InputHandler* inputHandler;
    
    Renderer* renderer;
    Node* node;
    std::vector<Node*> nodes;
    Window* window;
};

#endif /* defined(__Dominus__Engine__) */
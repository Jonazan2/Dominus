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

class Engine {
public:
    Engine();
    ~Engine();
    
    void init();
    void processInput();
    void update(double delta);
    void render();
    
    bool isRunning();
private:
    bool running;
    Scene* scene;
    GameScene* gameScene;
};

#endif /* defined(__Dominus__Engine__) */
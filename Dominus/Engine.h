//
//  Engine.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 27/01/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef __Dominus__Engine__
#define __Dominus__Engine__

#include <stdio.h>

class Engine {
public:
    Engine();
    ~Engine();
    
    void processInput();
    void update();
    void render();
    
    bool isRunning();
private:
    bool running;
};

#endif /* defined(__Dominus__Engine__) */
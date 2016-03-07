//
//  GameScene.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 16/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef Dominus_GameScene_h
#define Dominus_GameScene_h

#include "Scene.h"
#include <vector>
#include "Event.h"

class GameScene {
public:
    virtual void onSceneCreated( Scene* scene ) = 0;
    virtual void onUpdate( double delta ) = 0;
    virtual void onCosumeInput( std::vector<Event*>* ) = 0;
};
#endif

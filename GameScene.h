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

class GameScene {
public:
    virtual void onSceneCreated( Scene* scene ) = 0;
    virtual void onMouseDragged(double xRel, double yRel) = 0;
    virtual void onMouseClicked(double x, double y) = 0;
    virtual void onMouseReleased(double x, double y) = 0;
    virtual void onMouseMoved(double x, double y) = 0;
};
#endif

//
//  RenderScene.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 15/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef RenderScene_h
#define RenderScene_h

#include "GameScene.h"

class RenderScene : public GameScene {
public:
    RenderScene();
    ~RenderScene();
    
    void onSceneCreated( Scene* scene );
    void onMouseDragged(double xRel, double yRel);
    void onMouseClicked(double x, double y);
    void onMouseReleased(double x, double y);
    void onMouseMoved(double x, double y);
};

#endif /* RenderScene_h */

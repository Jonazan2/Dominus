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
    
    void onUpdate( double delta );
    void onKeyDown( int key );
    void onSceneCreated( Scene* scene );
    void onMouseDragged(double xRel, double yRel);
    void onMouseClicked(double x, double y);
    void onMouseReleased(double x, double y);
    void onMouseMoved(double x, double y);
    
    double delta;
    float yaw;
    float pitch;
    Scene* scene;
};

#endif /* RenderScene_h */

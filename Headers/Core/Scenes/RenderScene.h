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
    void onSceneCreated( Scene* scene );
    void onCosumeInput( std::vector<Event*>* );
    
    void onKeyDown( Event* event );
    void onMouseDragged( double xRel, double yRel );

    Scene* scene;
    
    double yaw;
    double pitch;
    
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    
    bool rightClickPressed;
    float xSaved;
    float ySaved;
};

#endif /* RenderScene_h */

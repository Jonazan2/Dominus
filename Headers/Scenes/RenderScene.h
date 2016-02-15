//
//  RenderScene.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 15/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef RenderScene_h
#define RenderScene_h

#include "Scene.h"

class RenderScene {
public:
    RenderScene();
    ~RenderScene();
    
    loadScene( Scene* scene );
};

#endif /* RenderScene_h */

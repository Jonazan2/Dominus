//
//  Scene.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include "INode.h"

class Scene {
public:
    Scene();
    ~Scene();
    
    void render();
private:
    INode* rootNode;
};

#endif /* Scene_h */

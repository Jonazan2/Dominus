//
//  Scene.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include "Renderer.h"
#include <glm/glm.hpp>
#include <stack>

class Scene {
public:
    Scene();
    ~Scene();
    
    void render();
    void pushMatrix( glm::mat4 matrix );
    glm::mat4 popMatrix();
private:
    Renderer* renderer;
    INode* rootNode;
    std::stack<glm::mat4> matrixStack;
};

#endif /* Scene_h */

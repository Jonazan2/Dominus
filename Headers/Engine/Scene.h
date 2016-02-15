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
#include <vector>
#include <glm/glm.hpp>
#include <stack>

class Scene {
public:
    Scene();
    ~Scene();
    
    void render();
    void load();
    void pushMatrix( glm::mat4 matrix );
    glm::mat4 popMatrix();
    void addToBatch( Node* node );
private:
    Renderer* renderer;
    INode* rootNode;
    std::stack<glm::mat4> matrixStack;
    std::vector< Node* > renderBatch;
};

#endif /* Scene_h */

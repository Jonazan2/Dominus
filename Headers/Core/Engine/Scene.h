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
#include "Camera.h"
#include "Layout.h"
#include <vector>
#include <glm/glm.hpp>
#include <stack>

class Scene {
public:
    Scene( Renderer* renderer );
    ~Scene();
    
    void update( double delta );
    void render();
    void load();
    void pushMatrix( glm::mat4 matrix );
    std::stack<glm::mat4> * getStack();
    glm::mat4 popMatrix();
    void addToBatch( Node* node );
    void addNode( INode* node );
    Camera* getCamera();
    void setCamera( Camera* camera );
    
    void setSceneHUD( UIComponent* );
    void renderUI();
private:
    Renderer* renderer;
    Node* rootNode;
    Camera* camera;
    glm::vec3 lightPosition;
    glm::mat4 projectionMatrix;
    std::stack<glm::mat4> matrixStack;
    std::vector< Node* > renderBatch;
    
    Layout* windowLayout;
};

#endif /* Scene_h */

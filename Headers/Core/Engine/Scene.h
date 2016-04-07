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
#include "LightNode.h"
#include <vector>
#include <glm/glm.hpp>
#include <stack>

class Scene {
public:
    static int generateID();
    
    Scene( Renderer* renderer );
    ~Scene();
    
    void update( double delta );
    void render();
    
    void render( Node* node, int renderState );
    void load( Node* node, int renderState );
    
    void pushMatrix( glm::mat4 matrix );
    std::stack<glm::mat4> * getStack();
    glm::mat4 popMatrix();
    void addNode( INode* node );
    Camera* getCamera();
    void setCamera( Camera* camera );
    LightNode* getLightNode();
    void setLightNode( LightNode* lightNode );
    
    void setMapNode( Node* node );
    
    void setSceneHUD( UIComponent* component );
    void loadUI();
private:
    Renderer* renderer;
    Layout* windowLayout;
    Node* rootNode;
    
    Camera* camera;
    LightNode* lightNode;
    Node* mapNode;
    
    std::stack< glm::mat4 > matrixStack;
    
    static int currentID;
};

#endif /* Scene_h */

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
    
    void render( std::shared_ptr<Node> node, int renderState );
    void load( std::shared_ptr<Node> node, int renderState );
    
    void pushMatrix( glm::mat4 matrix );
    std::stack<glm::mat4> * getStack();
    glm::mat4 popMatrix();
    void addNode( std::shared_ptr<INode> node );
    std::shared_ptr<Camera> getCamera();
    void setCamera( std::shared_ptr<Camera> camera );
    std::shared_ptr<LightNode> getLightNode();
    void setLightNode( std::shared_ptr<LightNode> lightNode );
    
    void setMapNode( std::shared_ptr<Node> node );
    
    void setSceneHUD( std::shared_ptr<UIComponent> component );
    void loadUI();
private:
    Renderer* renderer;
    
    std::shared_ptr<Layout> windowLayout;
    std::shared_ptr<Node> rootNode;
    
    std::shared_ptr<Camera> camera;
    std::shared_ptr<LightNode> lightNode;
    std::shared_ptr<Node> mapNode;
    
    std::stack< glm::mat4 > matrixStack;
    
    static int currentID;
    
};

#endif /* Scene_h */

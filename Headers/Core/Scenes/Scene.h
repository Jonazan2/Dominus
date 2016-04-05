#ifndef __Dominus_Scene_h__
#define __Dominus_Scene_h__

#include <vector>
#include <memory>
#include <stack>

#include <glm/glm.hpp>

#include "Renderer.h"
#include "Camera.h"
#include "Layout.h"
#include "LightNode.h"

class Scene {
public:
    Scene( Renderer* renderer );
    ~Scene();
    
    void load();
    void loadUI();
    void update( double delta );
    void render();
    
    void pushMatrix( glm::mat4 matrix );
    glm::mat4 popMatrix();
    
    void addToBatch( std::shared_ptr< Node > node );
    void addNode( std::shared_ptr< INode > node );

    void setMapNode( std::shared_ptr< Node > node );
    void setSceneHUD( std::shared_ptr< UIComponent > component );
    std::shared_ptr< std::stack< glm::mat4 > > getStack();
    void setCamera( std::shared_ptr< Camera > camera );
    std::shared_ptr< Camera > getCamera() const;
    void setLightNode( std::shared_ptr< LightNode > lightNode );
    std::shared_ptr< LightNode > getLightNode() const;
    
private:
    Renderer* renderer;
    Layout* windowLayout;
    Node* rootNode;
    
    std::shared_ptr< Camera > camera;
    std::shared_ptr< LightNode > lightNode;
    std::shared_ptr< Node > mapNode;
    
    std::shared_ptr< std::stack< glm::mat4 > > matrixStack;
    std::vector< std::shared_ptr< Node > > renderBatch;
};

#endif /* Scene_h */

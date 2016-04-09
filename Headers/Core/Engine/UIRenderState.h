//
//  UIRenderState.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 7/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef UIRenderState_h
#define UIRenderState_h

#include "RenderState.h"
#include "ShaderProgram.h"
#include "Buffer.h"

class UIRenderState : public RenderState {
public:
    UIRenderState();
    ~UIRenderState();
    
    void init( );
    void updateCamera( glm::mat4 camera );
    void updateProjection( glm::mat4 projection );
    void updateLightSource( glm::vec3 light );
    
    void load( std::shared_ptr<Node> node );
    void draw( std::shared_ptr<Node> node );
private:
    GLuint vao;
    
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::string positionAttributeKey;
    std::string textureAttributeKey;
    std::string mvpUniformKey;
    std::string textureDataUniformKey;
    
    std::shared_ptr<Buffer> uiVerticesBufer;
    std::shared_ptr<Buffer> uiUvsBuffer;
    
    std::unordered_map<int, long> offsetMap;
    int units;
};

#endif /* UIRenderState_h */

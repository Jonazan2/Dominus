//
//  MomoRenderState.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 2/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MomoRenderState_h
#define MomoRenderState_h

#include "RenderState.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "Drawer.h"

class MomoRenderState : public RenderState {
public:
    MomoRenderState();
    ~MomoRenderState();
    
    void init( );
    void updateCamera( glm::mat4 camera );
    void updateProjection( glm::mat4 projection );
    void updateLightSource( glm::vec3 light );
    
    void load( std::shared_ptr<Node> node );
    void draw( std::shared_ptr<Node> node );
private:
    std::shared_ptr<Drawer> drawer;
    std::shared_ptr<VertexArrayObject> vao;
    std::shared_ptr<ShaderProgram> shaderProgram;
    
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    glm::vec3 lightPosition;
    
    std::string positionAttributeKey;
    std::string normalAttributeKey;
    std::string textureAttributeKey;
    std::string modelViewUniformKey;
    std::string projectionUniformKey;
    std::string normalUniformKey;
    std::string lightUniformKey;
    std::string textureUniformKey;
    
    std::shared_ptr<Buffer> verticesBuffer;
    std::shared_ptr<Buffer> normalBuffer;
    std::shared_ptr<Buffer> uvsBuffer;
    
    std::unordered_map<int, long> offsetMap;
    int units;
};

#endif /* MomoRenderState_h */

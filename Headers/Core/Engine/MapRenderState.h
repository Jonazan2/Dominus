//
//  MapRenderState.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 2/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MapRenderState_h
#define MapRenderState_h

#include "RenderState.h"
#include "Buffer.h"
#include "ShaderProgram.h"

class MapRenderState : public RenderState {
public:
    MapRenderState();
    ~MapRenderState();
    
    void init( );
    void updateCamera( glm::mat4 camera );
    void updateProjection( glm::mat4 projection );
    void updateLightSource( glm::vec3 light );
    void load( std::vector< std::shared_ptr< Node > > renderBatch );
    void draw( std::vector< std::shared_ptr< Node > > renderBatch );
    
private:
    Buffer* normalBuffer;
    Buffer* verticesBuffer;
    
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    
    ShaderProgram* shaderProgram;
    
    std::string positionAttributeKey;
    std::string normalAttributeKey;
    std::string colorUniformKey;
    std::string projectionUniformKey;
    std::string modelViewUniformKey;
    
    GLuint vao;
};

#endif /* MapRenderState_h */

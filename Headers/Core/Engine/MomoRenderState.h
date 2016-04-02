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

class MomoRenderState : public RenderState {
public:
    MomoRenderState();
    ~MomoRenderState();
    
    void init( );
    void updateCamera( glm::mat4 camera );
    void updateProjection( glm::mat4 projection );
    void updateLightSource( glm::vec3 light );
    void load( std::vector<Node*> renderBatch );
    void draw( std::vector<Node*> renderBatch );
private:
    GLuint vao;
    GLuint shader_programme;
    
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    glm::vec3 lightPosition;
    
    GLuint positionAttribute;
    GLuint normalAttribute;
    GLuint textureAttribute;
    GLuint modelViewUID;
    GLuint projectionUID;
    GLuint normalUID;
    GLuint lightPositionUID;
    GLuint textureUID;
    
    Buffer* verticesBuffer;
    Buffer* normalBuffer;
    Buffer* uvsBuffer;
};

#endif /* MomoRenderState_h */

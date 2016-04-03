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

class MapRenderState : public RenderState {
public:
    MapRenderState();
    ~MapRenderState();
    
    void init( );
    void updateCamera( glm::mat4 camera );
    void updateProjection( glm::mat4 projection );
    void updateLightSource( glm::vec3 light );
    void load( std::vector<Node*> renderBatch );
    void draw( std::vector<Node*> renderBatch );
private:
    Buffer* normalBuffer;
    Buffer* verticesBuffer;
    
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    
    GLuint positionAttribute;
    GLuint normalAttribute;
    GLuint colorUniform;
    
    GLuint vao;
    GLuint shaderProgram;
    
    GLuint projectionUID;
    GLuint modelViewUID;
};

#endif /* MapRenderState_h */

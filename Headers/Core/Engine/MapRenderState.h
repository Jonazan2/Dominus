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
#include "VertexArrayObject.h"
#include <unordered_map>

class MapRenderState : public RenderState {
public:
    MapRenderState();
    ~MapRenderState();
    
    void init( );
    void updateCamera( glm::mat4 camera );
    void updateProjection( glm::mat4 projection );
    void updateLightSource( glm::vec3 light );
    
    void load( std::shared_ptr<Node> node );
    void draw( std::shared_ptr<Node> node );
private:
    std::shared_ptr<Buffer> normalBuffer;
    std::shared_ptr<Buffer> verticesBuffer;
    
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<VertexArrayObject> vao;
    
    std::string positionAttributeKey;
    std::string normalAttributeKey;
    std::string colorUniformKey;
    std::string projectionUniformKey;
    std::string modelViewUniformKey;
    
    std::unordered_map<int, long> offsetMap;
    int units;
};

#endif /* MapRenderState_h */

//
//  RenderState.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 2/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef RenderState_h
#define RenderState_h

#include "Node.hpp"

class RenderState {
public:
    virtual void init( ) = 0;
    virtual void updateCamera( glm::mat4 camera ) = 0;
    virtual void updateProjection( glm::mat4 projection ) = 0;
    virtual void updateLightSource( glm::vec3 light ) = 0;
    virtual void load( Node* node ) = 0;
    virtual void draw( Node* node ) = 0;
};

#endif /* RenderState_h */

//
//  LightNode.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 22/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef LightNode_h
#define LightNode_h

#include "INode.h"
#include <glm/glm.hpp>

class LightNode : public INode {
public:
    LightNode();
    ~LightNode();
    
    void onUpdate( );
    void onRestore( Scene* scene );
    void onRender( Scene* scene );
    void onRenderChildrends( Scene* scene );
    void onPostRender( Scene* scene );
    
    glm::vec3 position;
};

#endif /* LightNode_h */

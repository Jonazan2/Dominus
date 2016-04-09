//
//  MomoNode.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 7/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef MomoNode_h
#define MomoNode_h

#include "Node.hpp"

class MomoNode : public Node {
public:
    MomoNode();
    MomoNode( std::shared_ptr<Mesh> mesh );
    ~MomoNode();
    
    void onUpdate( );
    void onRestore( Scene* scene );
    void onRender( Scene* scene );
    void onRenderChildrends( Scene* scene );
    void onPostRender( Scene* scene );
};

#endif /* MomoNode_h */

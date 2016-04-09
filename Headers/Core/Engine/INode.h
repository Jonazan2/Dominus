//
//  INode.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 10/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef INode_h
#define INode_h

#include <memory>

class Scene;

class INode : public std::enable_shared_from_this<INode> {
public:
    virtual void onUpdate( ) = 0;
    virtual void onRestore( Scene* scene ) = 0;
    virtual void onRender( Scene* scene ) = 0;
    virtual void onRenderChildrends( Scene* scene ) = 0;
    virtual void onPostRender( Scene* scene ) = 0;
};

#endif /* INode_h */

//
//  MomoNode.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 7/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "MomoNode.h"
#include "Scene.h"

MomoNode::MomoNode( ) : Node() {

}

MomoNode::MomoNode( Mesh* mesh ) : Node( mesh ) {

}

MomoNode::~MomoNode() {

}

void MomoNode::onUpdate() {
    Node::onUpdate();
}

void MomoNode::onRestore( Scene *scene ) {
    Node::onRestore( scene );
    scene->load( this, Renderer::MOMO_RENDER_STATE );
}

void MomoNode::onRender( Scene *scene ) {
    Node::onRender( scene );
    scene->render( this, Renderer::MOMO_RENDER_STATE );
}

void MomoNode::onRenderChildrends( Scene *scene ) {
    Node::onRenderChildrends( scene );
}

void MomoNode::onPostRender( Scene* scene ) {
    Node::onPostRender( scene );
}

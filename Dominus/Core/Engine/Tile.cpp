//
//  Tile.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 31/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Tile.h"
#include "Scene.h"

Tile::Tile() : key( -1 )
{ }

Tile::~Tile() {

}

void Tile::onUpdate() {

}

void Tile::onRestore( Scene *scene ) {
    Node::onRestore( scene );
    scene->load( this, Renderer::MAP_RENDER_STATE );
}

void Tile::onRender( Scene *scene ) {
    Node::onRender( scene );
}

void Tile::onRenderChildrends( Scene *scene ) {
    Node::onRenderChildrends( scene );
}

void Tile::onPostRender( Scene* scene ) {
    scene->render( this, Renderer::MAP_RENDER_STATE );
    Node::onPostRender( scene );
}

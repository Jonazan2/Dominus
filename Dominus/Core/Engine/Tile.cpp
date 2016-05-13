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
    Node::onUpdate();
}

void Tile::onRestore( Scene *scene ) {
    Node::onRestore( scene );
    //TODO: provisional, will be implemented in futures user stories
    std::shared_ptr<Mesh> mesh = this->getMesh();
    std::shared_ptr<Shape> shape = mesh->getShapes().at( 0 );
    mesh->vertices = shape->vertices;
    mesh->uvs = shape->uvs;
    mesh->normals = shape->normals;
    scene->load( std::static_pointer_cast<Node>( shared_from_this() ),
                 Renderer::MAP_RENDER_STATE );
}

void Tile::onRender( Scene *scene ) {
    Node::onRender( scene );
    scene->render( std::static_pointer_cast<Node>( shared_from_this() ),
                   Renderer::MAP_RENDER_STATE );
}

void Tile::onRenderChildrends( Scene *scene ) {
    Node::onRenderChildrends( scene );
}

void Tile::onPostRender( Scene* scene ) {
    Node::onPostRender( scene );
}

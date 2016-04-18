#include "Mesh.hpp"

Mesh::Mesh()
    :texture( nullptr ) {
}

Mesh::Mesh( std::unique_ptr< MeshLoader > loader ) : Mesh( ) {
    this->loader = std::move( loader );
}

void Mesh::setTexture( std::shared_ptr<Texture> texture ){
    this->texture = texture;
}

std::shared_ptr<Texture> Mesh::getTexture() {
    return texture;
}

void Mesh::setMaterial( const Material material ) {
    this->material = material;
}

Material Mesh::getMaterial() const {
    return material;
}

Mesh::~Mesh() {
}
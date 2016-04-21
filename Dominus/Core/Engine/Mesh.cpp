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

std::vector<glm::vec3> Mesh::getVertices() const {
    std::vector<glm::vec3> result;
    return result;
}

std::vector<glm::vec2> Mesh::getUvs() const {
    std::vector<glm::vec2> result;
    return result;
}

std::vector<glm::vec3> Mesh::getNormals() const {
    std::vector<glm::vec3> result;
    return result;
}

Mesh::~Mesh() {
}
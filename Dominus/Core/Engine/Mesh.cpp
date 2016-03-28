#include "Mesh.hpp"
#include <OpenGL/OpenGL.h>

Mesh::Mesh()
:texture( nullptr )
{}

glm::vec3 Mesh::getPosition() const {
    return position;
}

void Mesh::setPosition( glm::vec3 position ) {
    this->position = position;
}

std::vector<glm::vec3> Mesh::getVertices() const {
    return vertices;
}

void Mesh::setUvs( std::vector<glm::vec2> uvs ) {
    this->textureVertices = uvs;
}

void Mesh::setVertices( std::vector<glm::vec3> vertices ) {
    this->vertices = vertices;
}

std::vector<glm::vec2> Mesh::getUvs() const {
    return textureVertices;
}

std::vector<glm::vec3> Mesh::getNormals() const {
    return normalVertices;
}

void Mesh::setTexture( Texture* texture ){
    this->texture = texture;
}

Texture* Mesh::getTexture() {
    return texture;
}

void Mesh::setMaterial( const Material material ) {
    this->material = material;
}

Material Mesh::getMaterial() const {
    return material;
}

Mesh::~Mesh() {}
#include "Mesh.hpp"

Mesh::Mesh()
    :texture( nullptr ) {
}

Mesh::Mesh( std::unique_ptr< MeshLoader > loader ) : Mesh( ) {
    this->loader = std::move( loader );
}

void Mesh::load( const std::string file ) {
    loader->load( file, &vertices, &uvs, &normals );
}

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
    this->uvs = uvs;
}

void Mesh::setVertices( std::vector<glm::vec3> vertices ) {
    this->vertices = vertices;
}

std::vector<glm::vec2> Mesh::getUvs() const {
    return uvs;
}

std::vector<glm::vec3> Mesh::getNormals() const {
    return normals;
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
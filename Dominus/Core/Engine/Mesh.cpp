#include "Mesh.hpp"

Mesh::Mesh()
    :texture( nullptr ) {
}

Shape::Shape() {

}

Shape::~Shape() {

}

long Shape::vecticesBufferSize() {
    return ( sizeof( GLfloat ) * 3 ) * vertices.size();
}

long Shape::uvsBufferSize() {
    return ( sizeof( GLfloat ) * 2 ) * uvs.size();
}

long Shape::normalsBufferSize() {
    return ( sizeof( GLfloat ) * 3 ) * normals.size();
}

Mesh::Mesh( std::unique_ptr< MeshLoader > loader ) : Mesh( ) {
    this->loader = std::move( loader );
}

void Mesh::addShape( std::shared_ptr<Shape> shape ) {
    shapes.push_back( shape );
}

void Mesh::setTexture( std::shared_ptr<Texture> texture ){
    this->texture = texture;
}

std::vector<std::shared_ptr<Shape>> Mesh::getShapes() {
    return shapes;
}

std::shared_ptr<Texture> Mesh::getTexture() {
    return texture;
}

std::vector<glm::vec3> Mesh::getVertices() const {
    return vertices;
}

std::vector<glm::vec2> Mesh::getUvs() const {
    return uvs;
}

std::vector<glm::vec3> Mesh::getNormals() const {
    return normals;
}

Mesh::~Mesh() {
}
#include "Mesh.hpp"
#include <OpenGL/OpenGL.h>

Mesh::Mesh() : rotationAngle( 0 ) {}

Mesh::Mesh( std::string filePath ) : rotationAngle( 0 ), fileName( filePath ) {
    vertexIndices = 0;
    uvIndices = 0;
    normalIndices = 0;
    numTriangles = 0;
    loadObj(filePath);
}

void Mesh::loadObj( std::string filePath ) {
    fileName = filePath;
    std::string line;
    std::ifstream file(filePath);
    
    if (file.is_open()) {
        std::vector<glm::vec3*> *tempVertices = new std::vector<glm::vec3 *>;
        std::vector<glm::vec2*> *tempTextureVertices = new std::vector<glm::vec2 *>;
        std::vector<glm::vec3*> *tempNormalsVertices = new std::vector<glm::vec3 *>;
        std::vector<int> *tempIndices = new std::vector<int>;
        
        while (std::getline(file, line)) {
            std::istringstream in(line);
            
            if (line.at(0) != '#') {
                
                float x, y, z;
                std::string type;
                in >> type;
                
                if( type == "v" ){
                    in >> x >> y >> z;
                    tempVertices->push_back( new glm::vec3(x,y,z) );
                }else if( type == "vt" ){
                    in >> x >> y;
                    tempTextureVertices->push_back( new glm::vec2(x,y) );
                }else if( type == "vn" ){
                    in >> x >> y >> z;
                    tempNormalsVertices->push_back( new glm::vec3(x,y,z) );
                }else if( type == "f" ) {
                    std::vector<std::string> triplets = split(line, ' ');
                    for ( std::string triplet : triplets ) {
                        std::vector<std::string> elements = split(triplet, '/');
                        
                        if (elements.size() == 2) {
                            // Although we can parse v//vn we are not handling this case
                            // while creating the final vertex list just yet
                            tempIndices->push_back(std::stoi(elements.at(0))); // v
                            tempIndices->push_back(std::stoi(elements.at(1))); // vn
                        } else if (elements.size() == 3) {
                            tempIndices->push_back(std::stoi(elements.at(0))); // v
                            tempIndices->push_back(std::stoi(elements.at(1))); // vt
                            tempIndices->push_back(std::stoi(elements.at(2))); // vn
                        }
                    }
                } else if ( type == "mtlib" || type == "usemtl" ) {
                    // We handle just one material per obj, but there could be
                    // multiple ones
                    std::string name;
                    in >> name;
                    material.loadMaterial(name);
                }
            }
        }
        
        // Reserve memory before hand for vertices
        numTriangles = (int)tempIndices->size() / 9;
        vertices.reserve(numTriangles);
        textureVertices.reserve(numTriangles);
        normalVertices.reserve(numTriangles);
        
        // Traverse faces list and create sorted list of vertices
        const int tempIndicesSize = (int) tempIndices->size();
        for( int i = 0; i < tempIndicesSize; i++ ){
            vertices.push_back(*tempVertices->at(tempIndices->at(i) - 1));
            textureVertices.push_back( *tempTextureVertices->at(tempIndices->at(++i) - 1) );
            normalVertices.push_back( *tempNormalsVertices->at(tempIndices->at(++i) -1) );
        }
        
        // Free temporary vectors
        for ( auto vertex : *tempVertices ) {
            delete vertex;
        }
        delete tempVertices;
        
        for ( auto vertex : *tempTextureVertices ) {
            delete vertex;
        }
        delete tempTextureVertices;
        
        for ( auto vertex : *tempNormalsVertices ) {
            delete vertex;
        }
        delete tempNormalsVertices;
        
        delete tempIndices;
    }
    file.close();
}
    
std::vector<std::string> Mesh::split( const std::string s, const char delimiter ) const {
    std::vector<std::string> elements;
    if ( !s.empty() ) {
        std::stringstream ss(s);
        std::string token;
        
        while(getline(ss, token, delimiter)) {
            elements.push_back(token);
        }
    } else {
        elements.push_back(s);
    }
    
    return elements;
}

std::string Mesh::getTexture() const {
    return texture;
}

void Mesh::setTexture( const std::string texture ) {
    this->texture = texture;
}

float Mesh::getRotationAngle() const {
    return rotationAngle;
}

void Mesh::setRotationAngle( float rotationAngle ) {
    this->rotationAngle = rotationAngle;
}

glm::vec3 Mesh::getPosition() const {
    return position;
}

void Mesh::setPosition( glm::vec3 position ) {
    this->position = position;
}

glm::vec3 Mesh::getRotation() const {
    return rotation;
}

void Mesh::setRotation( glm::vec3 rotation ) {
    this->rotation = rotation;
}

std::vector<glm::vec3> Mesh::getVertices() const {
    return vertices;
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

int Mesh::getNumTriangles() {
    return numTriangles;
}

GLsizeiptr Mesh::getSize() const {
    return ( sizeof ( GLfloat ) * 3 ) * vertices.size();
}

GLsizeiptr Mesh::getNormalVerticesSize() const {
    return ( sizeof ( GLfloat ) * 3 ) * normalVertices.size();
}

GLsizeiptr Mesh::getTextureVerticesSize() const {
    return ( sizeof( GLfloat ) * 2 ) * textureVertices.size();
}

void Mesh::setMaterial( const Material material ) {
    this->material = material;
}

Material Mesh::getMaterial() const {
    return material;
}

Mesh::~Mesh() {}
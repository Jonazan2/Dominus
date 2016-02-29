//
//  Mesh.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Mesh.hpp"
#include <OpenGL/OpenGL.h>

Mesh::Mesh()
{}

Mesh::Mesh(int numVertices) : rotationAngle(0)
{
    vertices = std::vector<glm::vec3>(numVertices);
}

Mesh::Mesh(std::string filePath) : rotationAngle(0), name( filePath )
{
    vertexIndices = 0;
    uvIndices = 0;
    normalIndices = 0;
    numTriangles = 0;
}

Mesh::~Mesh()
{

}

void Mesh::loadObj(std::string filePath)
{
    name = filePath;
    std::string line;
    std::ifstream file(filePath);
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUvs;
    std::vector<glm::vec3> tempNormals;
    std::vector<int> tempIndices;
    
    while (std::getline(file, line)) {
        std::istringstream in(line);
        std::string type;
        in >> type;
        float x, y, z;
        char separator = '/';
        int vertexIndice, uvIndice, normalIndice;
        std::vector<std::string> indices = std::vector<std::string>(3);
        if(type == "v"){
            in >> x >> y >> z;
            tempVertices.push_back(glm::vec3(x,y,z));
        }else if(type == "vt"){
            in >> x >> y;
            tempUvs.push_back(glm::vec2(x,y));
        }else if(type == "vn"){
            in >> x >> y >> z;
            tempNormals.push_back(glm::vec3(x,y,z));
        }else if(type == "f"){
            for(int i = 0; i < 3; i++){
                in >> indices[i];
                std::istringstream indicesStream(indices[i]);
                indicesStream >> vertexIndice >> separator >> uvIndice >> separator >> normalIndice;
                tempIndices.push_back(vertexIndice);
                tempIndices.push_back(uvIndice);
                tempIndices.push_back(normalIndice);
            }
        }
    }
    
    for(int i = 0; i < tempIndices.size(); ){
        int indice = tempIndices[i];
        vertices.push_back(tempVertices[indice - 1]);
        i++;
        indice = tempIndices[i];
        uvs.push_back(tempUvs[indice -1]);
        i++;
        indice = tempIndices[i];
        normals.push_back(tempNormals[indice -1]);
        i++;
    }
    numTriangles = (int)tempIndices.size() / 9;
    file.close();
}

std::string Mesh::getTexture() {
    return texture;
}

void Mesh::setTexture( std::string texture ) {
    this->texture = texture;
}

float Mesh::getRotationAngle(){
    return rotationAngle;
}

void Mesh::setRotationAngle( float rotationAngle ){
    this->rotationAngle = rotationAngle;
}

glm::vec3 Mesh::getPosition()
{
    return position;
}

void Mesh::setPosition(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Mesh::getRotation()
{
    return rotation;
}

void Mesh::setRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
}

std::vector<glm::vec3> Mesh::getVertices()
{
    return vertices;
}

void Mesh::setVertices(std::vector<glm::vec3> vertices)
{
    this->vertices = vertices;
}

std::vector<glm::vec2> Mesh::getUvs()
{
    return uvs;
}

std::vector<glm::vec3> Mesh::getNormals()
{
    return normals;
}

int Mesh::getNumTriangles()
{
    return numTriangles;
}

GLsizeiptr Mesh::getSize() {
    return ( sizeof ( GLfloat ) * 3 ) * vertices.size();
}

GLsizeiptr Mesh::getNormalSize() {
    return ( sizeof ( GLfloat ) * 3 ) * normals.size();
}

GLsizeiptr Mesh::getUVSize() {
    return ( sizeof( GLfloat ) * 2 ) * uvs.size();
}

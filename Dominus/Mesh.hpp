//
//  Mesh.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream> 
#include <fstream>
#include <istream>
#include <sstream>
#include <list>

class Mesh{
public:
    Mesh();
    Mesh(std::string filePath);
    Mesh(int numVertices);
    ~Mesh();
    
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::vec3 getRotation();
    void setRotation(glm::vec3 rotation);
    std::vector<glm::vec3> getVertices();
    void setVertices(std::vector<glm::vec3> vertices);
    void loadObj(std::string fileName);
    std::vector<glm::vec2> getUvs();
    int getNumTriangles();
private:
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
    int vertexIndices;
    int uvIndices;
    int normalIndices;
    int numTriangles;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
};

#endif /* Mesh_hpp */

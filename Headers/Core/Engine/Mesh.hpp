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
#include <OpenGL/gl3.h>
#include <string>
#include <vector>
#include <iostream> 
#include <fstream>
#include <istream>
#include <sstream>
#include <list>
#include <Material.hpp>
#include "Texture.h"

class Mesh{
public:
    Mesh();
    Mesh( std::string filePath );
    
    void loadObj(std::string fileName);
    
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 position);
    glm::vec3 getRotation() const;
    void setRotation(glm::vec3 rotation);
    std::vector<glm::vec3> getVertices() const;
    void setVertices(std::vector<glm::vec3> vertices);
    void setUvs(std::vector<glm::vec2> uvs);
    std::vector<glm::vec2> getUvs() const;
    std::vector<glm::vec3> getNormals() const;
    float getRotationAngle() const;
    void setRotationAngle(float);
    void setTexture( const std::string );
    std::string getTexturePath() const;
    int getNumTriangles();
    void setMaterial( const Material material );
    Material getMaterial() const;
    void setTexture( Texture* texture );
    Texture* getTexture();
    
    GLsizeiptr getSize() const;
    GLsizeiptr getNormalVerticesSize() const;
    GLsizeiptr getTextureVerticesSize() const;
    
    GLuint textureUID;
    
    ~Mesh();
private:
    std::string fileName;
    glm::vec3 position;
    glm::vec3 rotation;
    
    // TODO (jonathan): move this method to a Utils inline file ?
    std::vector<std::string> split( const std::string, const char ) const;
    
    float rotationAngle;
    int vertexIndices;
    int uvIndices;
    int normalIndices;
    int numTriangles;
    
    Material material;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureVertices;
    std::vector<glm::vec3> normalVertices;
    std::string texturePath;
    Texture* texture;
};

#endif /* Mesh_hpp */

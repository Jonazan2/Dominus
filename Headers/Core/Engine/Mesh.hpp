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
#include "Material.hpp"
#include "Texture.h"
#include "MeshLoader.h"

class Mesh{
public:
    Mesh( );
    Mesh( MeshLoader* loader );
    ~Mesh( );
    
    void load( const std::string file );
    
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 position);
    
    std::vector<glm::vec3> getVertices() const;
    void setVertices(std::vector<glm::vec3> vertices);
    
    void setUvs(std::vector<glm::vec2> uvs);
    std::vector<glm::vec2> getUvs() const;
    
    std::vector<glm::vec3> getNormals() const;
    
    void setMaterial( const Material material );
    Material getMaterial() const;
    
    void setTexture( std::shared_ptr<Texture> texture );
    std::shared_ptr<Texture> getTexture();
    
    void normalize();
    void unNormalize();
    
private:
    glm::vec3 position;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::shared_ptr<Texture> texture;
    Material material;
    MeshLoader* loader;
    bool normalized;
};

#endif /* Mesh_hpp */

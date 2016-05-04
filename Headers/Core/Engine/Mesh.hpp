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
#include "Material.h"
#include "Texture.h"
#include "MeshLoader.h"

#include <OpenGL/OpenGL.h>

struct ShapeInfo {
public:
    ShapeInfo() : material( "" ) {
    
    }
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    std::vector<std::vector<std::vector<int>>> indices;
    
    std::string material;
};

struct ObjInfo {
    ObjInfo() : materialLib( "" ) {
    }
    std::vector<std::shared_ptr<ShapeInfo>> shapes;
    std::string materialLib;
};

class Shape {
public:
    Shape();
    ~Shape();
    
    long vecticesBufferSize();
    long uvsBufferSize();
    long normalsBufferSize();
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
};

class Mesh {
public:
    Mesh();
    Mesh( std::unique_ptr< MeshLoader > loader );
    ~Mesh();
    
    std::vector<glm::vec3> getVertices() const;
    void setVertices(std::vector<glm::vec3> vertices);
    
    void setUvs(std::vector<glm::vec2> uvs);
    std::vector<glm::vec2> getUvs() const;
    
    std::vector<glm::vec3> getNormals() const;
    
    void setTexture( std::shared_ptr<Texture> texture );
    std::shared_ptr<Texture> getTexture();
    
    void addShape( std::shared_ptr<Shape> shape );
    
private:
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<Texture> texture;
    Material material;
    std::unique_ptr< MeshLoader > loader;
};

#endif /* Mesh_hpp */

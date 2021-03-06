//
//  ShaderProgram.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 3/4/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <OpenGL/gl3.h>
#include <string>
#include <vector>
#include "Shader.h"
#include <unordered_map>

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    
    int getUID();
    bool isLinked();
    void attachShader( std::shared_ptr<Shader> shader  );
    void linkProgram();
    void registerAttribute( std::string attributeKey );
    void registerUnitform( std::string uniformKey );
    
    GLuint getAttribute( std::string attributeKey );
    GLuint getUniform( std::string uniformKey );
    
    void useProgram();
    void releaseProgram();
private:
    GLuint uid;
    bool linked;
    bool active;
    std::vector<std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, GLuint> attributes;
    std::unordered_map<std::string, GLuint> uniforms;
};

#endif /* ShaderProgram_h */

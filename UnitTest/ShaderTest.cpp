//
//  ShaderTest.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 29/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Shader.h"
#include <gtest/gtest.h>

class ShaderTest : public ::testing::Test {
protected:
    ShaderTest() {
        type = GL_VERTEX_SHADER;
        filePath = "vertex_shader.glsl";
        shader = new Shader( filePath, type );
    }
    
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    GLenum type;
    std::string filePath;
    Shader* shader;
    
};

TEST_F( ShaderTest, IntegrationShaderTest ) {
    shader->load();
}

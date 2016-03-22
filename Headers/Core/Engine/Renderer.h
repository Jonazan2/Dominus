//
//  Renderer.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/02/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef __Dominus__Renderer__
#define __Dominus__Renderer__

#include <stdio.h>
#include "Mesh.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Node.hpp"
#include "Texture.h"
class UIComponent;

class Renderer{
public:
    Renderer( GLFWwindow* window );
    ~Renderer();
    void init();
    
    void updateProjection( glm::mat4 projectionMatrix );
    void updateLightSource( glm::vec3 lightSource );
    void updateViewMatrix( glm::mat4 viewMatrix );
    
    void load( std::vector<Node*> renderBatch );
    void draw( std::vector<Node*> renderBatch );
    
    void loadUI( );
    void drawUI(  );
    
    void drawtexture( UIComponent* component );
    
    void present();
    void clear();
private:
    void initOpenGLStates();
    void loadShaders();
    void loadUIShaders();
    
    GLFWwindow* window;
    GLuint vao;
    GLuint shader_programme;
    
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    glm::vec3 lightPosition;
    
    GLuint positionAttribute;
    GLuint normalAttribute;
    GLuint textureAttribute;
    GLuint modelViewUID;
    GLuint projectionUID;
    GLuint normalUID;
    GLuint lightPositionUID;
    GLuint textureUID;
    
    GLuint uiShaderProgram;
    GLuint uiPositionAttribute;
    GLuint uiMVPMatrix;
    GLuint uiTextureAttribute;
    GLuint uiTextureData;
    
    std::vector<UIComponent*> uiComponents;
};

#endif /* defined(__Dominus__Renderer__) */

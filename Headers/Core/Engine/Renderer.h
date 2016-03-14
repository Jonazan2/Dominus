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
#include "UIComponent.h"

class Renderer{
public:
    Renderer( GLFWwindow* window );
    ~Renderer();
    void init();
    void compileShader(GLuint shader);
    void onMouseDragged(double xRel, double yRel);
    void onMouseClicked(double x, double y);
    void onMouseReleased(double x, double y);
    void onMouseMoved(double x, double y);
    
    void updateProjection( glm::mat4 projectionMatrix );
    void updateLightSource( glm::vec3 lightSource );
    void updateCamera( glm::mat4 viewMatrix );
    void loadMesh( std::vector<Node*> renderBatch );
    void draw( std::vector<Node*> renderBatch );
    void initUI();
    void loadUI( std::vector<UIComponent*> uiComponents );
    void drawUI( std::vector<UIComponent*> uiComponents );
    void present();
private:
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
};

#endif /* defined(__Dominus__Renderer__) */

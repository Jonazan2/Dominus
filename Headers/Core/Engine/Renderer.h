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
#include "Buffer.h"
#include "GLGpuBuffer.h"
#include <unordered_map>
#include "RenderState.h"

class UIComponent;

class Renderer{
public:
    enum { MOMO_RENDER_STATE = 1 };
    enum { MAP_RENDER_STATE = 2 };
    
    Renderer( GLFWwindow* window );
    ~Renderer();
    void init();
    
    void updateState( const int stateCode );
    
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
    void loadUIShaders();
    
    static const GLuint BUFFER_SIZE = 100000 * 12;
    GLFWwindow* window;
    GLuint vao;
    
    GLuint uiShaderProgram;
    GLuint uiPositionAttribute;
    GLuint uiMVPMatrix;
    GLuint uiTextureAttribute;
    GLuint uiTextureData;
    
    Buffer* uiVerticesBufer;
    Buffer* uiUvsBuffer;
    
    std::vector<UIComponent*> uiComponents;
    std::unordered_map<int, RenderState*> states;
    RenderState* currentState;
};

#endif /* defined(__Dominus__Renderer__) */

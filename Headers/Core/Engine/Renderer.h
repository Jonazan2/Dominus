#ifndef __Dominus__Renderer__
#define __Dominus__Renderer__

#include <stdio.h>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"
#include "Node.hpp"
#include "Texture.h"
#include "Buffer.h"
#include "GLGpuBuffer.h"
#include "RenderState.h"
#include "ShaderProgram.h"

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
    
    void load( std::shared_ptr<Node> node );
    void draw( std::shared_ptr<Node> node );
    
    void loadUI( );
    void drawUI(  );
    
    void drawtexture( std::shared_ptr<UIComponent> component );
    
    void present();
    void clear();
private:
    void initOpenGLStates();
    void loadUIShaders();
    
    static const GLuint BUFFER_SIZE = 100000 * 12;
    GLFWwindow* window;
    GLuint vao;
    
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::string positionAttributeKey;
    std::string textureAttributeKey;
    std::string mvpUniformKey;
    std::string textureDataUniformKey;
    
    std::shared_ptr<Buffer> uiVerticesBufer;
    std::shared_ptr<Buffer> uiUvsBuffer;
    
    std::vector< std::shared_ptr< UIComponent > > uiComponents;
    std::unordered_map<int, RenderState*> states;
    RenderState* currentState;
};

#endif /* defined(__Dominus__Renderer__) */

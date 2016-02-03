//
//  main.cpp
//  Dominus
//
//  Created by Jonathan Contreras on 25/01/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <thread>
#include "Engine.h"
#include "Renderer.h"
const int FPS = 60; //Overall max frame rate
const double DELAY_TIME = 1000.0f / FPS;
const int MS_PER_UPDATE = 40; //25 FPS
void openglExample(){
    if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return ;
    }
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent (window);
    
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    /* OTHER STUFF GOES HERE NEXT */
    float points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };
    
    GLuint vbo = 0;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "uniform mat4 mvp;"
    "void main () {"
    "  gl_Position = mvp * vec4 (vp, 1.0);"
    "}";
    
    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";
    
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, NULL);
    glCompileShader (vs);
    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, NULL);
    glCompileShader (fs);
    
    GLuint shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);
    GLuint mvp = glGetUniformLocation(shader_programme, "mvp");
    
    while (!glfwWindowShouldClose (window)) {
        // wipe the drawing surface clear
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0,0,10),
                                           glm::vec3(0,0,0),
                                           glm::vec3(0.0f, 1.0f, 0.0f)
                                           );
        glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 1.0f);
        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
        
        glUseProgram (shader_programme);
        glUniformMatrix4fv(mvp, 1, GL_FALSE, &mvpMatrix[0][0]);
        glBindVertexArray (vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays (GL_TRIANGLES, 0, 3);
        // update other events like input handling
        glfwPollEvents ();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers (window);
    }
    
    // close GL context and any other GLFW resources
    glfwTerminate();

}

int main(int argc, const char * argv[]) {
    openglExample();
    Engine * engine = new Engine();
    std::chrono::time_point<std::chrono::system_clock> current, previous;
    previous = std::chrono::system_clock::now();
    double lag = 0.0;
//    Renderer* renderer = new Renderer;
//    renderer->init();
//    Mesh* mesh = new Mesh;
//    mesh->loadObj("cube.obj");
//    renderer->loadMesh(mesh);
    while(engine->isRunning()){
        current = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (current - previous);
        previous = current;
        lag += elapsed.count();
        
        engine->processInput();
        while (lag >= MS_PER_UPDATE) {
            engine->update();
            lag -= MS_PER_UPDATE;
        }
        engine->render();
//        renderer->render();
        if(elapsed.count() < DELAY_TIME){
            int waitTime = (int)(DELAY_TIME - elapsed.count());
            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
        }
    }
    
    return 0;
}

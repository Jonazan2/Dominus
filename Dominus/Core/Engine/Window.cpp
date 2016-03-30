//
//  Window.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "Window.h"
#include "Log.hpp"

Window::Window( int width, int height )
: width(width), height(height) {
    
}

Window::~Window() {

}

void Window::initWindow() {
    //Init window
    if (!glfwInit ()) {
        Log::getInstance().e("ERROR: could not start GLFW3\n");
        return ;
    }
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow ( width, height, "", NULL, NULL );
    if (!window) {
        Log::getInstance().e("ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent (window);
}

GLFWwindow* Window::windowHandler() {
    return window;
}
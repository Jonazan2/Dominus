//
//  GLFWInputHandler.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "GLFWInputHandler.h"

GLFWInputHandler* instance;

GLFWInputHandler::GLFWInputHandler( GLFWwindow* window ) :
                                                        window( window ) {
    instance = this;
}

GLFWInputHandler::~GLFWInputHandler() {

}

static void cursor_position_callback( GLFWwindow* window,
                                     double xpos, double ypos ) {

    if( instance != nullptr ){
        instance->onMouseMoved( xpos, ypos );
    }
}

void mouse_button_callback( GLFWwindow* window,
                           int button, int action, int mods ) {
    double xpos, ypos;
    if ( button == GLFW_MOUSE_BUTTON_RIGHT ) {
        glfwGetCursorPos( window, &xpos, &ypos );
        if( instance != nullptr ){
            instance->onRightClickEvent( action, xpos, ypos );
        }
    } else if( button == GLFW_MOUSE_BUTTON_LEFT ) {
        glfwGetCursorPos( window, &xpos, &ypos );
        if( instance != nullptr ) {
            instance->onLeftClickEvent( action, xpos, ypos );
        }
    }
}

void key_callback( GLFWwindow* window, int key,
                  int scancode, int action, int mode ) {
    if( instance != nullptr ){
        instance->onKeyEvent( key, scancode, action, mode );
    }
}

void window_close_callback( GLFWwindow* window ) {
    if( instance != nullptr ) {
        instance->onWindowClosed();
    }
}

void GLFWInputHandler::onKeyEvent(  int key, int scancode,
                                    int action, int mode ) {
    std::shared_ptr<Event> event( new Event );
    if ( action == GLFW_PRESS ) {
        event->type = ON_KEY_PRESS;
        event->keyCode = key;
    } else if ( action == GLFW_RELEASE ) {
        event->type = ON_KEY_RELEASE;
        event->keyCode = key;
    }
    events.push_back( event );
}

void GLFWInputHandler::onMouseMoved( double x, double y ) {
    std::shared_ptr<Event> event( new Event );
    event->type = ON_MOUSE_MOVED;
    event->x = x;
    event->y = y;
    events.push_back( event );
}

void GLFWInputHandler::onWindowClosed() {
    std::shared_ptr<Event> event( new Event );
    event->type = ON_WINDOW_CLOSED;
    events.push_back( event );
}

void GLFWInputHandler::onRightClickEvent( int action, double x, double y ) {
    std::shared_ptr<Event> event( new Event );
    event->x = x;
    event->y = y;
    if( action == GLFW_PRESS ) {
        event->type = ON_RIGHT_CLICK_PRESS;
    }else if( action == GLFW_RELEASE ) {
        event->type = ON_RIGHT_CLICK_RELEASE;
    }
    events.push_back( event );
}

void GLFWInputHandler::onLeftClickEvent( int action, double x, double y ) {
    std::shared_ptr<Event> event( new Event );
    event->x = x;
    event->y = y;
    if( action == GLFW_PRESS ) {
        event->type = ON_LEFT_CLICK_PRESS;
    }else if( action == GLFW_RELEASE ) {
        event->type = ON_LEFT_CLICK_RELEASE;
    }
    events.push_back( event );
}

void GLFWInputHandler::init() {
    glfwSetKeyCallback( window, key_callback );
    glfwSetCursorPosCallback( window, cursor_position_callback );
    glfwSetMouseButtonCallback( window,mouse_button_callback );
    glfwSetWindowCloseCallback( window, window_close_callback );
}

std::vector<std::shared_ptr<Event>>* GLFWInputHandler::poolEvents() {
    glfwPollEvents ();
    return &events;
}
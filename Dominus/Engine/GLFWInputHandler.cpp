//
//  GLFWInputHandler.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "GLFWInputHandler.h"
#include "Log.hpp"

GLFWInputHandler* instance;

GLFWInputHandler::GLFWInputHandler( GLFWwindow* window ) :
                                                        window( window ),
                                                        onDrag( false ),
                                                        onHoldKey( false ){
    instance = this;
    event = new Event;
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
    double xrelease, yrelease;
    if ( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS ){
        glfwGetCursorPos( window, &xpos, &ypos );
        
    }else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ){
        glfwGetCursorPos( window, &xpos, &ypos );
        
        if( instance != nullptr ){
            instance->onMouseClicked( xpos, ypos );
        }
    }else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE ){
        glfwGetCursorPos( window, &xrelease, &yrelease );
        if( instance != nullptr ){
            instance->onMouseReleased( xrelease, yrelease );
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
    Log::getInstance() << "window closed";
    if( instance != nullptr ) {
        instance->onWindowClosed();
    }
}

void GLFWInputHandler::onKeyEvent(  int key, int scancode,
                                    int action, int mode ) {
    if ( action == GLFW_PRESS ) {
        event->type = ON_KEY_EVENT;
        event->keyCode = key;
        onHoldKey = true;
    } else if ( action == GLFW_RELEASE ) {
        onHoldKey = false;
    }
}

void GLFWInputHandler::onMouseMoved( double x, double y ) {
    if( onDrag ){
        double xRel = x - event->x;
        double yRel = y - event->y;
        onMouseDragged( xRel, yRel );
    }
}

void GLFWInputHandler::onWindowClosed() {
    event->type = ON_WINDOW_CLOSED;
}

void GLFWInputHandler::onMouseClicked( double x, double y ) {
    event->type = ON_CLICK_DOWN;
    event->x = x;
    event->y = y;
    onDrag = true;
}

void GLFWInputHandler::onMouseReleased( double x, double y ) {
    event->type = ON_CLICK_RELEASE;
    event->x = x;
    event->y = y;
    onDrag = false;
}

void GLFWInputHandler::onMouseDragged( double xRel, double yRel ) {
    event->type = ON_MOUSE_DRAG;
    event->xRelative = xRel;
    event->yRelative = yRel;
}

void GLFWInputHandler::init() {
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);
}

Event* GLFWInputHandler::poolEvent() {
    // update other events like input handling
    glfwPollEvents ();
    Event* pooledEvent;
    if( !onHoldKey ){
        pooledEvent = new Event( event );
        event = new Event;
        return pooledEvent;
    }
    return event;
}
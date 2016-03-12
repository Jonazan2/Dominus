//
//  GLFWInputHandler.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef GLFWInputHandler_h
#define GLFWInputHandler_h

#include "InputHandler.h"
#include "Window.h"
#include <GLFW/glfw3.h>

class GLFWInputHandler : public InputHandler {
public:
    GLFWInputHandler( GLFWwindow* window );
    ~GLFWInputHandler();
    
    void init();
    std::vector<Event*> * poolEvents();

    void onRightClickEvent( int action, double x, double y );
    void onLeftClickEvent( int action, double x, double y );
    void onMouseMoved( double x, double y );
    void onKeyEvent( int key, int scancode, int action, int mode );
    void onWindowClosed();
private:
    GLFWwindow* window;
    std::vector<Event*> events;
};

#endif /* GLFWInputHandler_h */

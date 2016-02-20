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
    Event* poolEvent();
    void onMouseDragged( double xRel, double yRel );
    void onMouseClicked( double x, double y );
    void onMouseReleased( double x, double y );
    void onMouseMoved( double x, double y );
    void onWindowClosed();
private:
    bool onDrag;
    GLFWwindow* window;
    Event* event;
};

#endif /* GLFWInputHandler_h */

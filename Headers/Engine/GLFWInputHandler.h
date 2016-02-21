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
#include <stack>

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
    void onKeyEvent( int key, int scancode, int action, int mode );
    void onWindowClosed();
private:
    bool onHoldKey;
    bool onDrag;
    GLFWwindow* window;
    Event* event;
    double xSaved;
    double ySaved;
};

#endif /* GLFWInputHandler_h */

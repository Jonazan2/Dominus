//
//  Window.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Window_h
#define Window_h

#include <GLFW/glfw3.h>

class Window {
public:
    Window( int width, int height );
    ~Window();
    
    GLFWwindow* windowHandler();
    void initWindow();
private:
    int width;
    int height;
    GLFWwindow* window;
};

#endif /* Window_h */

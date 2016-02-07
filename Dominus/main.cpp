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
#include <Log.hpp>

const int FPS = 60; //Overall max frame rate
const double DELAY_TIME = 1000.0f / FPS;
const int MS_PER_UPDATE = 40; //25 FPS

int main(int argc, const char * argv[]) {    
    Engine * engine = new Engine();
    
    std::chrono::time_point<std::chrono::system_clock> current, previous;
    previous = std::chrono::system_clock::now();
    double lag = 0.0;
    Renderer* renderer = new Renderer;
    renderer->init();
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
        renderer->render();
        if(elapsed.count() < DELAY_TIME){
            int waitTime = (int)(DELAY_TIME - elapsed.count());
            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
        }
    }
    
    return 0;
}

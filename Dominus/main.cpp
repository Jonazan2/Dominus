#include <iostream>
#include <thread>
#include <memory>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include <MemoryUtils.h>
#include "Engine.h"
#include "Renderer.h"
#include <Log.hpp>

const int FPS = 60; // Overall max frame rate
const double DELAY_TIME = 1000.0f / FPS;
const int MS_PER_UPDATE = 40; //25 FPS

int main(int argc, const char * argv[]) {
    std::unique_ptr<Engine> engine( new Engine() );
    engine->init();
    
    std::chrono::time_point<std::chrono::system_clock> current, previous;
    previous = std::chrono::system_clock::now();
    double lag = 0.0;
    while(engine->isRunning()){
        current = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast
            < std::chrono::milliseconds > (current - previous);
        previous = current;
        lag += elapsed.count();
        
        engine->processInput();
        while ( lag >= MS_PER_UPDATE ) {
            engine->update( elapsed.count() );
            lag -= MS_PER_UPDATE;
        }
        engine->render();
        
        if( elapsed.count() < DELAY_TIME ){
            int waitTime = (int)(DELAY_TIME - elapsed.count());
            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
        }
    }
    
    return 0;
}

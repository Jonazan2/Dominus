#ifndef LoggerTerminal_hpp
#define LoggerTerminal_hpp

#include <string>
#include <iostream>
#include "Logger.hpp"

/**
 *  \brief     Logger class that logs strings to the terminal
 *
 *  \author    Jonathan Maldonado
 *  \date      09/02/2016
 */
class LoggerTerminal : public Logger {
    public:
        void write( const std::string& msg ) {
            std::cout << msg << std::endl;
        }
    
    ~LoggerTerminal() {};
};


#endif /* LoggerTerminal_hpp */

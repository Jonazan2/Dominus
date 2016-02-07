//
//  LoggerTerminal.h
//  Dominus
//
//  Created by Jonathan Contreras on 05/02/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef LoggerTerminal_hpp
#define LoggerTerminal_hpp

#include <string>
#include <iostream>
#include "Logger.hpp"

class LoggerTerminal : public Logger {
    public:
        void write(const std::string& msg) {
            std::cout << msg << std::endl;
        }
    
    ~LoggerTerminal() {};
};


#endif /* LoggerTerminal_hpp */

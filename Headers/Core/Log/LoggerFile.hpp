//
//  LoggerFile.h
//  Dominus
//
//  Created by Jonathan Maldonado Contreras on 7/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef LoggerFile_h
#define LoggerFile_h

#include <string>
#include <iostream>
#include <sstream>
#include <Logger.hpp>


class LoggerFile : public Logger {
public:
    void write(const std::string& msg) {
        os << msg << std::endl;
    }
    
    ~LoggerFile() {
        std::ofstream outfile ("log.txt");
        if (outfile.is_open()) {
            outfile << os.str() << std::endl;
        }
        outfile.close();
        os.flush();
    };
    
private:
    std::ostringstream os;
};



#endif /* LoggerFile_h */

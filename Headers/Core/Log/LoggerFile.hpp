#ifndef LoggerFile_hpp
#define LoggerFile_hpp

#include <string>
#include <iostream>
#include <sstream>
#include <Logger.hpp>

/**
 *  \brief     Logger class that logs strings into a file at the end
 *             of the execution
 *
 *  \author    Jonathan Maldonado
 *  \date      09/02/2016
 */
class LoggerFile : public Logger {
    public:
        void write( const std::string& msg ) {
            os << msg << std::endl;
        }
    
        ~LoggerFile() {
            std::ofstream outfile ("log.txt");
            if ( outfile.is_open() ) {
                outfile << os.str() << std::endl;
            }
            outfile.close();
            os.flush();
        };
    
    private:
        std::ostringstream os;
};



#endif /* LoggerFile_hpp */

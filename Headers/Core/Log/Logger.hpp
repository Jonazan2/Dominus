#ifndef Logger_hpp
#define Logger_hpp

#include <string>
#include <iostream>

/**
 *  \brief     Interface with the common behaviour of a Logger
 *
 *  \author    Jonathan Maldonado
 *  \date      09/02/2016
 */
class Logger {
    public:
        virtual void write( const std::string& ) = 0;
        virtual ~Logger() {};
};

#endif /* Logger_hpp */

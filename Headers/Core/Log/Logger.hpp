#ifndef Logger_hpp
#define Logger_hpp

#include <string>
#include <iostream>

class Logger {
    public:
        virtual void write(const std::string&) = 0;
        virtual ~Logger() {};
};

#endif /* Logger_hpp */

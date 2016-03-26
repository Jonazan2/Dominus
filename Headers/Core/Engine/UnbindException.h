//
//  UnbindException.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 24/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef UnbindException_h
#define UnbindException_h

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

class UnbindException : public std::runtime_error {
public:
    UnbindException( int bufferUID )
    : runtime_error( "Buffer unbind" ), bufferUID( bufferUID )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << ": " << bufferUID;
        
        return message.str().c_str();
    }

private:
    int bufferUID;
};

#endif /* UnbindException_h */

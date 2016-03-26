//
//  Exception.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 26/3/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Exception_h
#define Exception_h

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

class FileAccesException : public std::runtime_error {
public:
    FileAccesException( const char* fileName )
    : runtime_error( "Error accesing the file" ), fileName( fileName )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << " " << fileName;
        return message.str().c_str();
    }
    
private:
    const char* fileName;
    
};

class LibPngException : public std::runtime_error {
public:
    LibPngException( const char* error )
    : runtime_error( "Error reading png " ), error( error )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << ": " << error;
        return message.str().c_str();
    }
private:
    const char* error;
};

#endif /* Exception_h */

//
//  OpenGLExceptions.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/05/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef Dominus_OpenGLExceptions_h
#define Dominus_OpenGLExceptions_h

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

class UnbindException : public std::runtime_error {
public:
UnbindException( int uid )
: runtime_error( "Buffer unbinded" ), uid( uid )
{}

virtual const char* what() const throw() {
    std::ostringstream message;
    message << std::runtime_error::what() << " " << uid;
    return message.str().c_str();
    }
private:
    int uid;
};
    
class LinkProgramException : public std::runtime_error {
public:
    LinkProgramException( const char* error )
    : runtime_error( "Error linking program " ), error( error )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << ": " << error;
        return message.str().c_str();
    }
private:
    const char* error;
};

class ProgramNotLinkedException : public std::runtime_error {
public:
    ProgramNotLinkedException( int uid )
    : runtime_error( "Program not linked " ), uid( uid )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << ": " << uid;
        return message.str().c_str();
    }
private:
    int uid;
};

class UnknowAttributeException : public std::runtime_error {
public:
    UnknowAttributeException( const char* key )
    : runtime_error( "Attribute/Uniform not found " ), key( key )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << ": " << key;
        return message.str().c_str();
    }
private:
    const char* key;
};


#endif

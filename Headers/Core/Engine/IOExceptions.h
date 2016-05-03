//
//  IOExceptions.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 03/05/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef Dominus_IOExceptions_h
#define Dominus_IOExceptions_h

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

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

class FileNotFoundException : public std::runtime_error {
public:
    FileNotFoundException( const char* file )
    : runtime_error( "File not found " ), file( file )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << ": " << file;
        return message.str().c_str();
    }
private:
    const char* file;
};

class ParseException : public std::runtime_error {
public:
    ParseException( const char* message )
    : runtime_error( "Parse Exception" ), key( message )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << key;
        return message.str().c_str();
    }
private:
    const char* key;
};


#endif

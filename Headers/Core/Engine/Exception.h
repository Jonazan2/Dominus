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

class InvalidTextureException : public std::runtime_error {
public:
    InvalidTextureException( int uid, int width, int height )
    : runtime_error( "Invalid Texture" ),  uid( uid ), width( width ), height( height )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << " ";
        message << uid << " width: " << width << " height: " << height;
        return message.str().c_str();
    }
private:
    int uid;
    int width;
    int height;
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

#endif /* Exception_h */

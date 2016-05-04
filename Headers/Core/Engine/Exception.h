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
        
class ObjFormatException : public std::runtime_error {
public:
    ObjFormatException( const char* error )
    : runtime_error( "Bad format parsing Obj " ), error( error )
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

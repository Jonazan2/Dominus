//
//  StringStream.cpp
//  Dominus
//
//  Created by Alvaro Chambi Campos on 29/04/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#include "StringStream.h"
#include "MemoryUtils.h"

StringStream::StringStream()
: fileStream( nullptr ), filePath( "" ) {

}

StringStream::~StringStream() {
    
}

void StringStream::load( std::string filePath ) {
    this->filePath = filePath;
    this->fileStream =
        make_unique<std::ifstream>( std::ifstream( filePath ) );
}

std::istream& StringStream::getLine( std::string& line ) {
    //TODO: improve error handling
    if( fileStream != nullptr && fileStream->is_open() ) {
        return std::getline( *fileStream, line );
    } else {
        //throw exception
    }
    //don't know what to return here...
    return *fileStream;
}

std::string StringStream::peekLine() {
    std::string line = "";
    if( !fileStream->eof() ) {
        long current = fileStream->tellg();
        std::getline( *fileStream, line );
        // Return to position before "Read line".
        fileStream->std::__1::ios_base::clear();
        fileStream->seekg( current ,std::ios_base::beg );
    } else {
        //throw exception
    }
    return line;
}

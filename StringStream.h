//
//  StringStream.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 29/04/16.
//  Copyright (c) 2016 frikazos. All rights reserved.
//

#ifndef Dominus_StringStream_h
#define Dominus_StringStream_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
//TODO: maybe implement an iterator for the file( line per line )
class StringStream {
public:
    StringStream();
    ~StringStream();
    
    void load( std::string filePath );
    
    std::istream& getLine( std::string& );
    std::string peekLine( );
    std::unique_ptr<std::ifstream> fileStream;
private:
    std::string filePath;
    
};

#endif

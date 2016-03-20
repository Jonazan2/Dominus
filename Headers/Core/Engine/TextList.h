//
//  List.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 14/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__List__
#define __ProjectWar__List__

#include <stdio.h>
#include "VerticalLayout.h"
#include <string>
#include <list>

class TextList : public VerticalLayout
{
public:
    TextList();
    ~TextList();
    
    void updateDataset();
    
    void setList(std::list<std::string> list);
    
};

#endif /* defined(__ProjectWar__List__) */

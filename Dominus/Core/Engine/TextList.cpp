//
//  List.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 14/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "TextList.h"
#include "Text.h"

TextList::TextList()
{

}

TextList::~TextList()
{

}

void TextList::updateDataset()
{

}

void TextList::setList(std::list<std::string> list)
{
    for (std::string item : list) {
        Text* text = new Text();
        text->setTextResource(item);
        text->setParams(Params(50,10,CENTER));
        
        this->addComponent(text);
    }
}
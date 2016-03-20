//
//  OnItemClickedListener.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_OnItemClickedListener_h
#define ProjectWar_OnItemClickedListener_h

class UIComponent;

class OnItemClickedListener
{
public:
    OnItemClickedListener(){}
    ~OnItemClickedListener(){}
    
    virtual void onItemClicked(UIComponent* component) = 0;
};
#endif

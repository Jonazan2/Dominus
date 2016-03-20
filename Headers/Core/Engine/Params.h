//
//  Params.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Params_h
#define ProjectWar_Params_h

static const int FILL = -1;
static const int WRAP = -2;

enum Gravity
{
    CENTER,
    UP,
    DOWN,
    RIGHT,
    CENTER_DOWN,
};

enum LayoutDisposition
{
    WEIGHT_DISPOSITION,
    WRAP_DISPOSITION,
};

class Params
{
public:
    Params() : width(FILL), height(FILL), gravity(CENTER), margin(0), marginLeft(0), marginRight(0)
                ,marginTop(0), marginDown(0), disposition(WRAP_DISPOSITION)
    {}
    Params(int width, int height, Gravity gravity) : Params()
    {
        this->width = width;
        this->height = height;
        this->gravity = gravity;
    }
    virtual ~Params(){}
    int width;
    int height;
    Gravity gravity;
    LayoutDisposition disposition;
    int marginLeft;
    int marginRight;
    int marginTop;
    int marginDown;
    //TODO margin not implemented
    int margin;
};

#endif

//
//  Event.h
//  Dominus
//
//  Created by Alvaro Chambi Campos on 20/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#ifndef Event_h
#define Event_h

enum EventType {
    ON_WINDOW_CLOSED,
    ON_RIGHT_CLICK_PRESS,
    ON_RIGHT_CLICK_RELEASE,
    ON_LEFT_CLICK_PRESS,
    ON_LEFT_CLICK_RELEASE,
    ON_KEY_PRESS,
    ON_KEY_RELEASE,
    ON_MOUSE_MOVED,
    EVENT_NONE
};

class Event {
public:
    Event( Event* event );
    Event();
    ~Event();
    
    EventType type;
    int x;
    int y;
    int keyCode;
    
    int xRelative;
    int yRelative;
    
    bool consumed;
};

#endif /* Event_h */

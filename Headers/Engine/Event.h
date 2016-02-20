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
    ON_CLICK_DOWN,
    ON_CLICK_RELEASE,
    ON_MOUSE_DRAG,
    EVENT_NONE
};

class Event {
public:
    Event();
    ~Event();
    
    EventType type;
    int x;
    int y;
    
    int xRelative;
    int yRelative;
};

#endif /* Event_h */

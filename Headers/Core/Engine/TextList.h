#ifndef __Dominus__List__
#define __Dominus__List__

#include <stdio.h>
#include <string>
#include <list>

#include "Text.h"
#include "VerticalLayout.h"

class TextList : public VerticalLayout {
public:
    TextList();
    ~TextList();
    
    void updateDataset();
    void setList( std::list<std::string> list);
    
};

#endif /* _TEXT_LIST_H_ */

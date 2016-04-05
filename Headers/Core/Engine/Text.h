#ifndef __Dominus__Text__
#define __Dominus__Text__

#include <stdio.h>
#include <iostream>
#include <memory>

#include "Texture.h"
#include "UIComponent.h"

class Text : public UIComponent {
public:

    Text();
    virtual ~Text();
    
    void render(Renderer* renderer);
    void setTextResource(std::string text);
    void setVisible(bool visible);
    void setTexture( std::shared_ptr< Texture > texture);

private:
    std::string resource;
    //Flag to know if the text resource has been changed
    bool changed;
};

#endif /* TEXT_H_ */

#ifndef __Dominus__Button_h__
#define __Dominus__Button_h__

#include <stdio.h>

#include "UIComponent.h"

class Button : public UIComponent {
public:
    Button();
    virtual ~Button();
    void render(Renderer* renderer);
    void setTexture(std::shared_ptr< Texture > texture);
    void setImageResource(std::string resource);
private:
    std::string resource;
    bool resourceChanged;
};

#endif /* _BUTTON_H_ */

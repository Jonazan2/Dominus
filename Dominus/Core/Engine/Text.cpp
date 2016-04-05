#include "Text.h"

Text::Text() : UIComponent(), resource(""),
               changed(false) {
}

void Text::render(Renderer *renderer) {}

void Text::setTexture( std::shared_ptr< Texture > texture ){
    this->texture = texture;
}

void Text::setVisible( bool visible ) { }

void Text::setTextResource( std::string text ) {
    this->resource = text;
    this->changed = true;
}

Text::~Text() {}
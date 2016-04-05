#include "Button.h"

Button::Button( )
    :resource(""),
    resourceChanged(false) {
}

void Button::render( Renderer *renderer ) {
    renderer->drawtexture( this );
}

void Button::setTexture( std::shared_ptr< Texture >texture ) {
    this->texture = texture;
}

void Button::setImageResource( std::string resource ) {
    this->resource = resource;
    resourceChanged = true;
}

Button::~Button() {}
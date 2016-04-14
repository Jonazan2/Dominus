#include "TextList.h"

TextList::TextList() {}

TextList::~TextList() {}

void TextList::updateDataset() {}

void TextList::setList( std::list<std::string> list ) {
    for ( std::string item : list ) {
        Text* text = new Text();
        text->setTextResource(item);
        Params params;
        params.width = 50;
        params.height = 10;
        params.gravity = CENTER;
        text->setParams(params);
        this->addComponent( std::shared_ptr< Text >( text ) );
    }
}
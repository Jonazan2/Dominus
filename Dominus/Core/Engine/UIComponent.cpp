#include "UIComponent.h"

UIComponent::UIComponent() : width(0), height(0), weight(0),hud(false), visible(true), texture(nullptr), parent(nullptr), listener(nullptr) {
    mesh = new Mesh;
}

void UIComponent::onMeasureCompleted() {}

void UIComponent::onMeasureChanged() {}

//TODO: Update event handling
bool UIComponent::handleEvent( const Event event ) {
    return false;
}

//TODO: Update render call
void UIComponent::render( Renderer* renderer ) {
    renderer->drawtexture( shared_from_this() );
}

std::shared_ptr<UIComponent> UIComponent::matchEvent( glm::vec2 position ) {
    return nullptr;
}

//TODO: Update resize logic
void UIComponent::resize( float widthRatio, float heightRatio ) {}

void UIComponent::resetSize() {}

void UIComponent::measureDimension() {
    switch ( params.width ) {
        case FILL:
            this->width = parent->width;
            break;
        case WRAP:
            this->width = texture->getWidth();
            break;
        default:
            this->width = params.width;
            break;
    }
    
    switch ( params.height ) {
        case FILL:
            this->height = parent->height;
            break;
        case WRAP:
            this->height = texture->getHeight();
            break;
        default:
            this->height = params.height;
            break;
    }
    if ( width < 0 ) {
        width = 0;
    }
    if ( height < 0 ){
        height = 0;
    }
}

void UIComponent::measurePosition(glm::vec2 parentPosition, int parentWidth,
                                  int parentHeight ) {
    if ( readjustDimension(parentWidth, parentHeight) ) {
        switch ( params.gravity ) {
            case CENTER:
                center(parentPosition, parentWidth, parentHeight);
                break;
            case CENTER_DOWN:
                centerDown(parentPosition, parentWidth, parentHeight);
                break;
            case UP:
                up(parentPosition, parentWidth, parentHeight);
                break;
            case DOWN:
                down(parentPosition, parentWidth, parentHeight);
                break;
            case RIGHT:
                right(parentPosition, parentWidth, parentHeight);
                break;
            default:
                break;
        }
        readjustPosition();
    }
}

void UIComponent::readjustPosition() {
    position.x = position.x + params.marginLeft;
    position.y = position.y + params.marginTop;
}

//rescale dimensions if needed (content bigger than container)
//return if the component could be drawed before the rescale (width, height > 0)
bool UIComponent::readjustDimension( int parentWidth, int parentHeight ) {
    bool result = true;
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    if ( virtualWidth > parentWidth ) {
        width = parentWidth - (params.marginLeft + params.marginRight);
    }
    if( virtualHeight > parentHeight ){
        height = parentHeight - (params.marginTop + params.marginDown);
    }
    
    if ( width < 0 ) {
        width = 0;
        result = false;
    }
    if ( height < 0 ){
        height = 0;
        result = false;
    }
    
    return result;
}

void UIComponent::centerDown( glm::vec2 parentPosition, int parentWidth,
                              int parentHeight ) {
    down( parentPosition, parentWidth, parentHeight );
    center( getPosition(), parentWidth, getHeight() );
}

void UIComponent::center( glm::vec2 parentPosition, int parentWidth,
                          int parentHeight) {
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;

    int centerX = parentPosition.x + ( parentWidth / 2 );
    int centerY = parentPosition.y + ( parentHeight / 2 );
    int offsetX = virtualWidth / 2;
    int offsetY = virtualHeight / 2;
    setPosition( centerX - offsetX, centerY - offsetY );
}

void UIComponent::up( glm::vec2 parentPosition, int parentWidth,
                      int parentHeight ) {
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int centerX = parentPosition.x + ( parentWidth / 2 );
    int offsetX = virtualWidth / 2 ;
    setPosition(centerX - offsetX, parentPosition.y);
}

void UIComponent::down( glm::vec2 parentPosition, int parentWidth,
                        int parentHeight){
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    int y = parentPosition.y + parentHeight - virtualHeight;
    int centerX = parentPosition.x + ( parentWidth / 2 );
    int offsetX = virtualWidth / 2;
    setPosition( centerX - offsetX, y );
}

void UIComponent::left( glm::vec2 parentPosition, int parentWidth,
                        int parentHeight ) {
    int virtualHeight = height + params.marginTop + params.marginDown;
    int centerY = parentPosition.y + ( parentHeight / 2 );
    int offsetY = virtualHeight / 2;
    setPosition(parentPosition.x, centerY - offsetY);
}

void UIComponent::right( glm::vec2 parentPosition, int parentWidth,
                         int parentHeight ) {
    int virtualWidth = width + params.marginLeft + params.marginRight;
    int virtualHeight = height + params.marginTop + params.marginDown;
    
    int centerY = parentPosition.y + ( parentHeight / 2 );
    int offsetY = virtualHeight / 2;
    
    int x = parentPosition.x + parentWidth - virtualWidth;
    setPosition(x, centerY - offsetY);
}

void UIComponent::setPosition( const int x, const int y ) {
    this->position.x = x;
    this->position.y = y;
}

void UIComponent::setPosition( const glm::vec2 position ) {
    this->position = position;
}

glm::vec2 UIComponent::getPosition() const {
    return position;
}

void UIComponent::setWidth( const int width ) {
    this->width = width;
}

int UIComponent::getWidth() const {
    return width;
}

void UIComponent::setHeight( const int height ) {
    this->height = height;
}

int UIComponent::getHeight() const {
    return height;
}

bool UIComponent::isVisible() {
    return visible;
}

void UIComponent::setVisible( const bool visible ) {
    this->visible = visible;
}

void UIComponent::setParent( UIComponent* component ) {
    this->parent = component;
}

UIComponent* UIComponent::getParent() const {
    return parent;
}

void UIComponent::setHUD( const bool hud ) {
    this->hud = hud;
}

bool UIComponent::isHUD() const {
    return hud;
}

void UIComponent::setParams( const Params params ) {
    this->params = params;
}

Params UIComponent::getParams() const {
    return this->params;
}

void UIComponent::setWeight( const int weight ) {
    this->weight = weight;
}

int UIComponent::getWeight() const {
    return this->weight;
}

void UIComponent::setMesh( Mesh* mesh ) {
    this->mesh = mesh;
}

Mesh* UIComponent::getMesh() const {
    return this->mesh;
}

void UIComponent::setTexture( std::shared_ptr< Texture > texture ) {
    this->texture = texture;
}

std::shared_ptr< Texture > UIComponent::getTexture() const {
    return this->texture;
}

void UIComponent::setFrame( const Frame frame ) {
    this->frame = frame;
}

Frame UIComponent::getFrame() {
    return this->frame;
}

UIComponent::~UIComponent() {
    std::cout << "UIComponent destroyed \n";
}
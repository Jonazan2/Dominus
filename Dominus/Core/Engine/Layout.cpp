#include "Layout.h"

Layout::Layout() :
    UIComponent() {
    backgroundTexture = nullptr;
}

//TODO: Implement render call
void Layout::render( Renderer *renderer ) {
    for ( std::shared_ptr< UIComponent > component : components ) {
        component->render( renderer );
    }
}

//When the layout and dimensions and position has been succesfully measured
void Layout::onMeasureCompleted() {
    this->measureDisposition();
}

//Whenever a layout dimensions or position is changed
void Layout::onMeasureChanged() {
    this->measureDisposition();
}

void Layout::onContentMeasureCompleted() {}

bool Layout::handleEvent( const Event event ) {
    bool result = false;
    for ( std::shared_ptr< UIComponent > component : components ) {
        if ( component->handleEvent( event ) ) {
            result = true;
            if ( listener != nullptr ) {
                listener->onItemClicked( component.get() );
            }
        }
    }
    return result;
}

void Layout::resize( float widthRatio, float heightRatio ) {
    UIComponent::resize( widthRatio, heightRatio );
    for ( std::shared_ptr< UIComponent >  component : components ) {
        component->resize( widthRatio, heightRatio );
        component->onMeasureChanged();
    }
    onMeasureChanged();
}

void Layout::resetSize() {
    UIComponent::resetSize();
    for ( std::shared_ptr< UIComponent > component : components ) {
        component->resetSize();
        component->onMeasureChanged();
    }
    onMeasureChanged();
}

//measure the distribution of the layout and places his components
void Layout::measureDisposition() {
    std::vector< glm::vec2 > dispositionPoints = layoutDisposition();
    assignFrames( dispositionPoints );
    populateLayout( dispositionPoints );
}

void Layout::populateLayout(std::vector<glm::vec2> dispositionPoints) {
    for ( std::shared_ptr< UIComponent > component : components ) {
        Frame frame = component->getFrame();
        component->measurePosition( frame.position, frame.width, frame.height );
        //Notify finished measurement
        component->onMeasureCompleted();
    }
    //All the components in the layout has been succesfully measured (just the first inner level)
    this->onContentMeasureCompleted();
}

void Layout::assignFrames(std::vector<glm::vec2> dispositionPoints) {
    std::vector<std::shared_ptr< UIComponent >>
        vector(components.begin(), components.end());
    assignFrames(dispositionPoints, vector);
}

void Layout::assignFrames( std::vector<glm::vec2> dispositionPoints, std::vector<std::shared_ptr< UIComponent >> components ) {
    int i = 0;
    for ( std::shared_ptr< UIComponent > component : components ) {
        glm::vec2 start = dispositionPoints.at( i++ );
        glm::vec2 end = dispositionPoints.at( i++ );
        Frame frame = component->getFrame();
        frame.position = start;
        frame.width = end.x - start.x;
        frame.height = end.y - start.y;
        component->setFrame(frame);
    }
}

std::vector<glm::vec2> Layout::layoutDisposition() {
    std::vector<glm::vec2> dispositionPoints;
    for ( int i = 0; i < components.size(); i++ ) {
        glm::vec2 start( position );
        glm::vec2 end( position.x + width, position.y + height );
        dispositionPoints.push_back( start );
        dispositionPoints.push_back( end );
    }
    return dispositionPoints;
}

void Layout::addComponent( std::shared_ptr< UIComponent > component ) {
    components.push_back( component );
    //update children hud value
    component->setHUD( this->isHUD() );
    //Update parent value: first use of the params
    component->setParent( this );
    component->measureDimension();
    //Position measure must consider the type of layout and the items in it
    this->measureDisposition();
}

void Layout::cleanComponents() {
    this->components.clear();
}
void Layout::setBackground( std::shared_ptr< Texture > background ) {
    this->backgroundTexture = background;
}

std::shared_ptr<UIComponent> Layout::matchEvent( glm::vec2 position ) {
        std::shared_ptr<UIComponent>result = nullptr;
    if( isVisible() ) {
        for ( std::shared_ptr< UIComponent > component : components ) {
            result = component->matchEvent( position );
            if ( result != nullptr ) {
                return result;
            }
        }
    }
    return result;
}

Layout::~Layout() {
    std::cout << "layout destroyed\n";
}

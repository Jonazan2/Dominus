#ifndef __Dominus_UIComponent_h__
#define __Dominus_UIComponent_h__

#include <memory>

#include "Renderer.h"
#include "Texture.h"
#include "Event.h"
#include "OnItemClickedListener.h"
#include "Mesh.hpp"

constexpr int FILL = -1;
constexpr int WRAP = -2;

enum Gravity {
    CENTER,
    UP,
    DOWN,
    RIGHT,
    CENTER_DOWN,
};

enum LayoutDisposition {
    WEIGHT_DISPOSITION,
    WRAP_DISPOSITION,
};

struct Params {
    int width = FILL;
    int height = FILL;
    Gravity gravity = CENTER;
    LayoutDisposition disposition = WRAP_DISPOSITION;
    int marginLeft;
    int marginRight;
    int marginTop;
    int marginDown;
    int margin;
};

struct Frame {
    glm::vec2 position;
    int width;
    int height;
};

class UIComponent : public std::enable_shared_from_this<UIComponent>{
public:
    UIComponent();
    virtual ~UIComponent();
    virtual void render( Renderer* renderer );
    virtual std::shared_ptr<UIComponent> matchEvent( glm::vec2 position );
    
    virtual bool handleEvent( const Event event );
    
    virtual void onMeasureCompleted();
    virtual void onMeasureChanged();
    
    virtual void resize( float widthRatio, float heightRatio );
    virtual void resetSize();
    
    void measureDimension();
    void measurePosition( glm::vec2 parentPosition,
                         int parentWidth,
                         int parentHeight );
    
    //readjust dimension when needed, never allowes a component higher or wider than the parent
    bool readjustDimension(int parentWidth, int parentHeight);
    //readjust component position to fix the margin displacement
    void readjustPosition();
    
    void center( glm::vec2 parentPosition, int parentWidth, int parentHeight ) ;
    void up( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void down( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void right( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void left( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    void centerDown( glm::vec2 parentPosition, int parentWidth, int parentHeight );
    
    void setHUD( const bool hud );
    bool isHUD() const;
    
    void setParams( const Params params );
    Params getParams() const;
    
    void setPosition( const int x, const int y );
    void setPosition( const glm::vec2 position );
    glm::vec2 getPosition() const;
    
    void setWidth( const int width );
    int getWidth() const;
    
    void setHeight( const int height );
    int getHeight() const;
    
    void setWeight( const int weight );
    int getWeight() const;
    
    void setVisible( bool visible );
    bool isVisible();
    
    void setParent( UIComponent* component );
    UIComponent* getParent() const;

    void setMesh( Mesh* mesh );
    Mesh* getMesh() const;
    
    void setTexture( std::shared_ptr< Texture > texture );
    std::shared_ptr< Texture > getTexture() const;
    
    void setFrame( const Frame frame );
    Frame getFrame();
    
protected:
    UIComponent* parent;
    Params params;
    glm::vec2 position;
    std::shared_ptr<Texture> texture;
    int width;
    int height;
    bool hud;
    bool visible;
    float weight;
    Frame frame;
    OnItemClickedListener* listener;
    Frame menuFrame;
    Mesh* mesh;
};

#endif

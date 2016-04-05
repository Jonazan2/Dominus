#include "Scene.h"

Scene::Scene( Renderer* renderer ) :
                                    renderer( renderer ),
                                    lightNode( nullptr ),
                                    camera( nullptr ) {
    rootNode = new Node;
    windowLayout = new Layout;
    matrixStack = std::shared_ptr<std::stack< glm::mat4 >> (new std::stack< glm::mat4 >());
    pushMatrix( glm::mat4( 1 ) );
}

void Scene::update( double delta ) {
    rootNode->onUpdate();
    if( camera != nullptr ) {
        renderer->updateProjection( camera->projectionMatrix );
        renderer->updateViewMatrix( camera->viewMatrix );
    }
    if( lightNode != nullptr ) {
        renderer->updateLightSource( lightNode->position );
    }
}

void Scene::setMapNode( std::shared_ptr< Node > node ) {
    this->mapNode = node;
}

std::shared_ptr< Camera > Scene::getCamera() const {
    return camera;
}

void Scene::setLightNode( std::shared_ptr< LightNode > lightNode ) {
    this->lightNode = lightNode;
    rootNode->addNode( lightNode );
}

void Scene::setCamera( std::shared_ptr< Camera > camera ) {
    this->camera = camera;
    rootNode->addNode( camera );
}

void Scene::setSceneHUD( std::shared_ptr< UIComponent > component ) {
    windowLayout->setWidth(640);
    windowLayout->setHeight(480);
    
    windowLayout->addComponent( component );
}

void Scene::loadUI() {
    //iterate graph and populate the batch
    windowLayout->render( renderer );
    //load batch in gpu memory
    renderer->loadUI();
}

void Scene::load() {
    //iterate the graph and populate the batch
    rootNode->onRestore( this );
    //load batch in gpu memory
    renderer->load( renderBatch );
    renderBatch.clear();
}

void Scene::addNode( std::shared_ptr< INode > node ) {
    rootNode->addNode( node );
}

void Scene::render() {
    if( camera != nullptr ){
        rootNode->onRender( this );
        rootNode->onRenderChildrends( this );
        rootNode->onPostRender( this );
        
        renderer->draw( renderBatch );
        renderBatch.clear();
    }
}

std::shared_ptr< std::stack< glm::mat4 > > Scene::getStack() {
    return matrixStack;
}

void Scene::pushMatrix( glm::mat4 matrix ) {
    matrixStack->push( matrix );
}

glm::mat4 Scene::popMatrix() {
    glm::mat4 result = matrixStack->top();
    matrixStack->pop();
    return result;
}

void Scene::addToBatch( std::shared_ptr< Node > node ) {
    renderBatch.push_back( node );
}

Scene::~Scene() {
    delete windowLayout;
    delete rootNode;
}
#include "RenderScene.h"

RenderScene::RenderScene() {
    upPressed = false;
    downPressed = false;
    leftPressed = false;
    rightPressed = false;
    rightClickPressed = false;
}

void RenderScene::onSceneCreated( Scene* scene ) {
    populateScene( scene );
    populateUI( scene );
}

void RenderScene::populateScene( Scene* scene ) {
    this->scene = scene;
   
    //Camera setup
    std::shared_ptr<Camera> camera( new Camera );
    camera->yaw = -45.0;
    camera->pitch = -25.0;
    camera->position = glm::vec3( -6.33f, 7.28f, 5.93f );
    scene->setCamera( camera );
    
    std::shared_ptr<LightNode> lightNode( new LightNode );
    scene->setLightNode( lightNode );
    //std::shared_ptr<Mesh> momoMesh( new Mesh( make_unique< ObjLoader >() ) );
    //momoMesh->load( "momo.obj" );
    
    std::shared_ptr<ObjLoader> loader =
        std::make_shared<ObjLoader>( ObjLoader( "momo.obj" ) );
    std::shared_ptr<MeshBuilder> meshBuilder =
        std::make_shared<MeshBuilder>( MeshBuilder() );
    std::shared_ptr<Mesh> momoMesh = meshBuilder->buildMesh( loader );

    std::shared_ptr<Texture> momoTexture( new Texture( make_unique<GLGpuTexture>(),
                                                       make_unique<PngTextureLoader>() ) );
    momoTexture->load( "diffuse.png" );
    momoMesh->setTexture( momoTexture );
    
    //populate scene
    std::shared_ptr<Node> momoNode( new MomoNode( momoMesh ) );
    momoNode->setModelMatrix( glm::translate( glm::vec3( 1.0f, 2.0f, -1.0f ) ) *
                             glm::rotate( -360.0f , glm::vec3( 1.0f, 0.0f, 0.0f ) ) *
                             glm::rotate( 90.0f , glm::vec3( 0.0f, 0.0f, 1.0f ) ) *
                             glm::scale( glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
    
    MapBuilder* mapBuilder = new MapBuilder;
    std::shared_ptr<Map> map = mapBuilder->build( new MapLoader( "map.lua" ) ,
                                  new TilesLoader( ) );
    map->addNode( momoNode );
    map->setup();
    
    map->setModelMatrix( glm::scale( glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
    
    scene->addNode( map );
}

void RenderScene::populateUI( Scene* scene ) {
    std::shared_ptr<HorizontalLayout> root( new HorizontalLayout );
    Params params = Params();
    params.disposition = WEIGHT_DISPOSITION;
    root->setParams(params);
    
    // Create buttons
    std::shared_ptr< Button > ptrButton( new Button );
    ptrButton->setWeight( 1 );
    std::shared_ptr< Button > ptrButton2( new Button );
    ptrButton2->setWeight( 1 );
    
    Texture* buttonTexture = new Texture( make_unique<GLGpuTexture>(),
                                          make_unique<PngTextureLoader>() );
    std::shared_ptr< Texture > ptrTexture( buttonTexture );
    
    Texture* button2Texture = new Texture( make_unique<GLGpuTexture>(),
                                          make_unique<PngTextureLoader>() );
    std::shared_ptr< Texture > ptrTexture2( button2Texture );

    ptrTexture->load( "button.png" );
    ptrTexture2->load( "button.png" );
    Params buttonParams = Params();
    buttonParams.width = WRAP;
    buttonParams.height = WRAP;
    buttonParams.gravity = DOWN;

    ptrButton2->setParams(buttonParams);
    ptrButton->setParams(buttonParams);
    ptrButton2->setTexture( ptrTexture2 );
    ptrButton->setTexture( ptrTexture );
    
    // Add components to scene
    scene->setSceneHUD( root );
    root->addComponent( ptrButton );
    root->addComponent( ptrButton2 );
    scene->loadUI();
}

void RenderScene::onUpdate( double delta ) {
    GLfloat cameraSpeed = 0.01f * delta;
    std::shared_ptr<Camera> camera = scene->getCamera();
    if( upPressed ) {
        camera->position += cameraSpeed * camera->front;
    }
    if( downPressed ){
        camera->position -= cameraSpeed * camera->front;
    }
    if( leftPressed ) {
        camera->position -= glm::normalize(glm::cross(camera->front,
                                camera->up)) * cameraSpeed;
    }
    if( rightPressed ) {
        camera->position += glm::normalize(glm::cross(camera->front,
                                camera->up)) * cameraSpeed;
    }
}

void RenderScene::onKeyDown( std::shared_ptr<Event> event ) {
    switch ( event->keyCode ) {
        case GLFW_KEY_UP:
            if ( event->type == ON_KEY_PRESS ) {
                upPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                upPressed = false;
            }
            break;
        case GLFW_KEY_DOWN:
            if ( event->type == ON_KEY_PRESS ) {
                downPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                downPressed = false;
            }
            break;
        case GLFW_KEY_LEFT:
            if ( event->type == ON_KEY_PRESS ) {
                leftPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                leftPressed = false;
            }
            break;
        case GLFW_KEY_RIGHT:
            if ( event->type == ON_KEY_PRESS ) {
                rightPressed = true;
            } else if ( event->type == ON_KEY_RELEASE ) {
                rightPressed = false;
            }
            break;
        default:
            break;
    }
    
}

void RenderScene::onMouseDragged( double xRel, double yRel ) {
    GLfloat sensitivity = 0.01;
    double xoffset = xRel * sensitivity;
    double yoffset = yRel * sensitivity;
    
    scene->getCamera()->yaw += xoffset;
    scene->getCamera()->pitch += yoffset;
}

void RenderScene::onCosumeInput( std::vector<std::shared_ptr<Event>>* events ) {
    for ( int i = 0; i < events->size(); i++ ) {
        std::shared_ptr<Event> event = events->at( i );
        if ( event->type == ON_RIGHT_CLICK_PRESS ) {
            event->consumed = true;
            xSaved = event->x;
            ySaved = event->y;
            rightClickPressed = true;
        } else if ( event->type == ON_RIGHT_CLICK_RELEASE ) {
            event->consumed = true;
            xSaved = 0;
            ySaved = 0;
            rightClickPressed = false;
        } else if ( event->type == ON_KEY_PRESS ) {
            event->consumed = true;
            onKeyDown( event );
        } else if ( event->type == ON_KEY_RELEASE ) {
            event->consumed = true;
            onKeyDown( event );
        } else if ( event->type == ON_MOUSE_MOVED ) {
            event->consumed = true;
            if ( rightClickPressed ) {
                onMouseDragged( event->x - xSaved, ySaved - event->y );
            }
        }
    }
}

RenderScene::~RenderScene() {}
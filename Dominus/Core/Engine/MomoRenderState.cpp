#include "MomoRenderState.h"
#include "GLGpuBuffer.h"
#include "Shader.h"

MomoRenderState::MomoRenderState()
    : units( 0 ) {
    verticesBuffer = std::shared_ptr<Buffer>(
                                new Buffer( make_unique< GLGpuBuffer >() ) );
    uvsBuffer = std::shared_ptr<Buffer>(
                                new Buffer( make_unique< GLGpuBuffer >() ) );
    normalBuffer = std::shared_ptr<Buffer>(
                                new Buffer( make_unique< GLGpuBuffer >() ) );
    
    vao = std::make_shared<VertexArrayObject>( VertexArrayObject() );
    
    shaderProgram = std::shared_ptr<ShaderProgram>( new ShaderProgram );
        
    drawer = std::make_shared<Drawer>( Drawer( vao, shaderProgram ) );
    
    textureUniformKey = "textureData";
    modelViewUniformKey = "modelViewMatrix";
    projectionUniformKey = "projectionMatrix";
    normalUniformKey = "normalMatrix";
    lightUniformKey = "lightPosition";
    
    positionAttributeKey = "vp";
    textureAttributeKey = "textureCoord";
    normalAttributeKey = "normalAttribute";
}

void MomoRenderState::updateCamera( glm::mat4 camera ) {
    this->viewMatrix = camera;
}

void MomoRenderState::updateProjection( glm::mat4 projection ) {
    this->projectionMatrix = projection;
}

void MomoRenderState::updateLightSource( glm::vec3 light ) {
    this->lightPosition = light;
}

void MomoRenderState::init() {
    std::shared_ptr<Shader> vertexShader =
        std::shared_ptr<Shader>( new Shader( "vertex_shader.glsl",
                                        GL_VERTEX_SHADER ) );
    vertexShader->compile();
    
    std::shared_ptr<Shader> fragmentShader =
        std::shared_ptr<Shader>( new Shader( "fragment_shader.glsl",
                                        GL_FRAGMENT_SHADER ) );
    fragmentShader->compile();
    
    shaderProgram->attachShader( vertexShader );
    shaderProgram->attachShader( fragmentShader );
    
    shaderProgram->linkProgram();
    
    shaderProgram->registerAttribute( positionAttributeKey );
    shaderProgram->registerAttribute( normalAttributeKey );
    shaderProgram->registerAttribute( textureAttributeKey );
    
    shaderProgram->registerUnitform( modelViewUniformKey );
    shaderProgram->registerUnitform( projectionUniformKey );
    shaderProgram->registerUnitform( normalUniformKey );
    shaderProgram->registerUnitform( lightUniformKey );
    shaderProgram->registerUnitform( textureUniformKey );
    
    vao->bind();
    
    verticesBuffer->bind();
    vao->mapAttribute( shaderProgram->getAttribute( positionAttributeKey ),
                          3, GL_FLOAT, GL_FALSE, 0, NULL);
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    vao->mapAttribute( shaderProgram->getAttribute( normalAttributeKey ),
                          3, GL_FLOAT, GL_FALSE, 0, NULL);
    normalBuffer->unBind();
    
    uvsBuffer->bind();
    vao->mapAttribute( shaderProgram->getAttribute( textureAttributeKey ),
                          2, GL_FLOAT, GL_FALSE, 0, NULL );
    uvsBuffer->unBind();
    
    vao->unBind();
}

void MomoRenderState::load( std::shared_ptr<Node> node ) {
    vao->bind();
    std::shared_ptr<Mesh> mesh = node->getMesh();
    
    verticesBuffer->bind();
    verticesBuffer->push( (float*) &mesh->vertices[0],
                         ( sizeof( GLfloat ) * 3 ) * mesh->vertices.size() );
    offsetMap[node->getID()] = units;
    units += mesh->vertices.size();
    verticesBuffer->unBind();
    
    normalBuffer->bind();
    normalBuffer->push( (float*)&mesh->normals[0],
                       ( sizeof ( GLfloat ) * 3 ) * mesh->normals.size() );
    normalBuffer->unBind();
    
    uvsBuffer->bind();
    uvsBuffer->push( (float*)&mesh->uvs[0],
                    ( sizeof ( GLfloat ) * 2 ) * mesh->uvs.size() );
    uvsBuffer->unBind();
    
    //Texture loading
    std::shared_ptr<Texture> texture = mesh->getTexture();
    if( texture != nullptr ){
        texture->bind();
        texture->push();
        texture->unbind();
    }
    vao->unBind();
}

void MomoRenderState::draw( std::shared_ptr<Node> node ) {
    
    shaderProgram->useProgram();
    vao->bind();
    vao->mapUniformMatrix4fv( shaderProgram->getUniform( projectionUniformKey ),
                        1, GL_FALSE, &projectionMatrix[0][0] );
    vao->mapUniform3fv( shaderProgram->getUniform( lightUniformKey ),
                  1, &lightPosition[0]);
    
    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->bind();
        vao->mapUniform1i( shaderProgram->getUniform( textureUniformKey ) , 0);
    }
    
    glm::mat4 modelViewMatrix = viewMatrix * *node->getToWorldMatrix();
    glm::mat4 normalMat = glm::transpose( glm::inverse( modelViewMatrix ) );
    glm::mat3 normalMat3 = glm::mat3( normalMat );
    vao->mapUniformMatrix4fv( shaderProgram->getUniform( modelViewUniformKey ),
                       1, GL_FALSE, &modelViewMatrix[0][0] );
    vao->mapUniformMatrix3fv( shaderProgram->getUniform( normalUniformKey ),
                       1, GL_FALSE, &normalMat3[0][0] );
    
    drawer->draw( GL_TRIANGLES,
                  (int)offsetMap[node->getID()],
                  (int)node->getMesh()->vertices.size() );

    if( node->getMesh()->getTexture() != nullptr ) {
        node->getMesh()->getTexture()->unbind();
    }

    vao->unBind();
    shaderProgram->releaseProgram();
}

MomoRenderState::~MomoRenderState() {
    
}
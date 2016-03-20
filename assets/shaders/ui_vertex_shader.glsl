#version 400
layout(location = 4) in vec3 vertexCoord;
layout(location = 5) in vec2 textureCoord;
out vec2 fragTextureCoord;
uniform mat4 modelViewProjectionMatrix;
void main () {
    fragTextureCoord = textureCoord;
    gl_Position = modelViewProjectionMatrix * vec4 (vertexCoord, 1.0);
}
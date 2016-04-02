#version 400
in vec3 vertex;
in vec3 color;

out vec3 outColor;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main () {
    outColor = color;
    mat4 mvpMatrix = projectionMatrix * modelViewMatrix;
    gl_Position = mvpMatrix * vec4 ( vertex, 1.0f );
}
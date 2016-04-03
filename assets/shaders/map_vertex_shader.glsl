#version 400
in vec3 vertex;
in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main () {
    gl_Position = projectionMatrix * modelViewMatrix * vec4 ( vertex, 1.0f );
}
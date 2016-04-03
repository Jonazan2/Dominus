#version 400
layout(location = 6) in vec3 vertex;
layout(location = 7) in vec3 color;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main () {
    gl_Position = projectionMatrix * modelViewMatrix * vec4 ( vertex, 1.0f );
}
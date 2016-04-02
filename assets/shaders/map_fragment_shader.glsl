#version 400
in vec3 color;
out vec4 fragmentColor;

void main () {
    fragmentColor = vec4( color.x, color.y , 1.0f , 1.0f );
}
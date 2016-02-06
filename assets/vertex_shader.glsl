#version 400
in vec3 vp;
in vec3 normal;
out vec3 color;
uniform mat4 mvp;
void main () {
    gl_Position = mvp * vec4 (vp, 1.0);
    color = normal;
}
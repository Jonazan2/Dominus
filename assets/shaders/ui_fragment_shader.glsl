#version 400
in vec2 fragTextureCoord;
out vec4 fragment_color;
uniform sampler2D textureData;
void main () {
    fragment_color = texture( textureData, fragTextureCoord );
}
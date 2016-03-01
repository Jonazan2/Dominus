#version 400
in vec3 lightColor;
in vec2 fragTextureCoord;
out vec4 frag_colour;
uniform sampler2D textureData;
void main () {
    frag_colour = vec4( lightColor, 1.0 ) * texture( textureData, fragTextureCoord );
}
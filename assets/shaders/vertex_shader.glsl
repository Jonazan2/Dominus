#version 400
in vec3 vp;
in vec3 normalAttribute;
in vec2 textureCoord;
out vec3 lightColor;
out vec2 fragTextureCoord;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
void main () {
    fragTextureCoord = textureCoord;
    vec3 position = vec3(modelViewMatrix * vec4(vp, 1.0));
    vec3 normal = normalize(normalMatrix * normalAttribute);
    vec3 lightDirection = normalize(lightPosition - position);
    float ndotl = max(dot(normal, lightDirection), 0.0);
    lightColor = ndotl * vec3( 1.0 );
    gl_Position = projectionMatrix * vec4 (position, 1.0);
};
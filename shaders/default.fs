#version 330 core

in vec2 texCoor;
out vec4 fragColor;

uniform sampler2D textureSampler;
void main (){
    // fragColor = vec4(1,.4, .6, 1);
    fragColor = texture(textureSampler, texCoor);
}
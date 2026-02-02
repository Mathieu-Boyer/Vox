#version 330 core

in vec2 texCoor;
flat in int texID;
out vec4 fragColor;

uniform sampler2DArray texArray; 
// uniform sampler2D textureSampler;
void main (){
    // fragColor = vec4(1,.4, .6, 1);
    fragColor = texture(texArray, vec3(texCoor, texID));
}
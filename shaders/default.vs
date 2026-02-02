#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 atexCoor;
layout (location = 2) in int aTexID;

out vec2 texCoor;
flat out int texID;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main (){
    gl_Position = projection * view  * (model * vec4(aPos, 1));
    texCoor = atexCoor;
    texID = aTexID;
}
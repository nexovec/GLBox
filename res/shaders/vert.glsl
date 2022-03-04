#version 450

in vec3 i_pos;
in vec3 i_color;

layout(location = 0) out vec3 o_color;

uniform mat4 i_globT;

void main(){
    o_color = vec3(i_color);
    // gl_Position = i_globT*vec4(i_pos,1.0);
    gl_Position = vec4(i_pos,1.0);
}
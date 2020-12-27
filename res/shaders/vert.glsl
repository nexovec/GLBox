#version 430
out vec3 out_color;
uniform mat4 globT;
in vec2 pos;
in vec3 color;
void main(){
    out_color = vec3(color);
    gl_Position = globT*vec4(pos,0.0,1.0);
}
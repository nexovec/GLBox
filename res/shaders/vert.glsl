#version 430
out vec3 out_color;
uniform mat4 globT;
in vec3 pos;
in vec3 color;
void main(){
    out_color = vec3(color);
    // gl_Position = globT*vec4(pos,1.0);
    gl_Position = vec4(pos,1.0);
}
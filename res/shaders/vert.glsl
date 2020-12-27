#version 430
out vec3 out_color;
in mat4 ortho;
in vec2 pos;
in vec3 color;
void main(){
    out_color = vec3(color);
    gl_Position = ortho*vec4(pos,0.0,1.0);
}
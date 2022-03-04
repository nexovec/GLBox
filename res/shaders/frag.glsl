#version 450

in vec3 o_color;

out vec4 o_FragColor;

void main(){
    o_FragColor = vec4(o_color,1.0);
}
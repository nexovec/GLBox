#version 450

layout(location = 0) in vec3 i_color;

out vec4 o_FragColor;

void main() { o_FragColor = vec4(i_color, 1.0); }
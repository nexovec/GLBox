#version 450 core

in vec2 o_tex_coord;
out vec4 o_FragColor;
uniform sampler2D our_texture;
void main() { o_FragColor = vec4(o_tex_coord.xy, 0.0, 1.0f); }
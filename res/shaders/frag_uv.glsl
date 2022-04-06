#version 450 core

layout(location = 1) in vec2 i_tex_coord;
out vec4 o_FragColor;
layout(binding = 0) uniform sampler2D our_texture;

void main() { o_FragColor = texture(our_texture, i_tex_coord); }
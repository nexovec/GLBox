#version 450 core

in vec2 o_tex_coord;
out vec4 o_FragColor;
uniform sampler2D our_texture;

void main() { o_FragColor = texture(our_texture, o_tex_coord); }
// void main() {
//     o_FragColor = vec4(o_tex_coord.xy, 0.0, 1.0f);
// }
// void main() { o_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); }
#version 450 core

in vec3 i_pos;
in vec3 i_color;
in vec2 i_tex_coord;

out vec2 o_tex_coord;

uniform mat4 i_globT;

void main() {
  gl_Position = i_globT * vec4(i_pos, 1.0);
  o_tex_coord = i_tex_coord;
}
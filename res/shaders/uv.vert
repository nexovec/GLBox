#version 450 core

in vec3 i_pos;
in vec2 i_tex_coords;

out vec2 o_tex_coords;
out vec3 fragWorldPos;

uniform mat4 i_globT;

void main() {
  gl_Position = i_globT * vec4(i_pos, 1.0);
  o_tex_coords = i_tex_coords;
  fragWorldPos = i_pos;
}

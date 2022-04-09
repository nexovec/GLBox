#version 450 core

in vec2 o_tex_coord;
in vec3 fragWorldPos;
out vec4 o_FragColor;
uniform sampler2D our_texture;

void main() {
  vec3 normal = normalize(cross(dFdx(fragWorldPos), dFdy(fragWorldPos)));
  vec4 tex_color = texture(our_texture, o_tex_coord);
  o_FragColor = vec4(tex_color.xyz, 1.0f);
}
// void main() {
//     o_FragColor = vec4(o_tex_coord.xy, 0.0, 1.0f);
// }
// void main() { o_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); }
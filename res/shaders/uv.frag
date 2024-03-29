#version 450 core

in vec2 o_tex_coords;
in vec3 fragWorldPos;
out vec4 o_FragColor;
uniform sampler2D our_texture;

void main() {
  vec3 normal = normalize(cross(dFdx(fragWorldPos), dFdy(fragWorldPos)));
  vec4 tex_color = texture(our_texture, o_tex_coords);
  float light_multiplier = abs(dot(normalize(vec3(0.0f, 1.0f, 1.0f)), normal));
  o_FragColor = vec4(tex_color.xyz, 1.0f);
}

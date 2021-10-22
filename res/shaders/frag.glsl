#version 430
in vec3 out_color;
out vec4 fragColor;
void main(){
    fragColor = vec4(out_color,1.0);
}
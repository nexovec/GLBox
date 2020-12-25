#version 430
in vec3 out_color;
out vec4 gl_FragColor;
void main(){
    gl_FragColor = vec4(out_color,1.0);
}
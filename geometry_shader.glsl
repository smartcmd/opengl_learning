#version 450 core

layout(traingles) in;
layout(points,max_vertices = 3) out;

void main() {
    for(int i = 0;i <gl_in.length();i++){
        gl_Position = gl_in[i];
        EmitVertex();
    }
}

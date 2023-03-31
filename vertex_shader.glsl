#version 450 core

layout(location = 0) in vec4 pos;
layout(location = 1) uniform mat4 mv_matrix;
layout(location = 2) uniform mat4 proj_matrix;

out vec4 vs_color;

void main(){
	gl_Position = proj_matrix * mv_matrix * pos;
	vs_color = pos * 2.0 + vec4(0.5,0.5,0.5,0.0);
}
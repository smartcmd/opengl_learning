#version 450 core

layout(triangles,equal_spacing,cw) in;

void main() {//the number of this method's invocation is due to the subvertices which are producted by the subdivision engine
    //gl_TessCoord is in changeing
    //gl_in[] is const and include the inital vertices(before subdivision)
    gl_Position = ((gl_TessCoord.x * gl_in[0].gl_Position) +
                    (gl_TessCoord.y * gl_in[1].gl_Position) +
                    (gl_TessCoord.z * gl_in[2].gl_Position));
}

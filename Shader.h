//
//  shader.hpp
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GL/gl3w.h"
//#include <OpenGL/glew.h> // 包含glew来获取所有的必须OpenGL头文件

class ShaderInfo{
public:
    const char * shader_path;
    const GLuint shader_type;
    ShaderInfo(const char * sp, const GLuint st) : shader_path(sp) , shader_type(st){};
};

class Shader
{
public:
    // 程序ID
    GLuint Program;
    // 构造器读取并构建着色器
    Shader(int length, const ShaderInfo shaderInfos[]);
    // 使用程序
    void use();
    void del();
};


#endif


#endif /* Shader_hpp */
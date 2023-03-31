#include "Shader.h"
#include <vector>

Shader::Shader(int length, const ShaderInfo shaderInfos[]){
    std::vector<GLuint> shaders;
    shaders.resize(length);

    // 着色器程序
    this->Program = glCreateProgram();

    for(int i = 0;i < length;i++){
        const char* path = shaderInfos[i].shader_path;
        const GLuint type = shaderInfos[i].shader_type;
        std::string code;
        std::ifstream file;
        file.exceptions(std::ifstream::badbit);
        try
        {
            std::stringstream shaderStream;
            // 打开文件
            file.open(path);
            // 读取文件的缓冲内容到流中
            shaderStream << file.rdbuf();
            // 关闭文件
            file.close();
            // 转换流至GLchar数组
            code = shaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* shaderCode = code.c_str();
        // 2. 编译着色器
        GLuint shader;
        GLint success;
        GLchar infoLog[512];

        shader = glCreateShader(type);
        shaders[i] = shader;
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        // 打印编译错误（如果有的话）
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        glAttachShader(this->Program, shader);
    }

    //链接程序
    glLinkProgram(this->Program);
    GLint link_status;
    GLchar link_infoLog[512];
    // 打印连接错误（如果有的话）
    glGetProgramiv(this->Program,GL_LINK_STATUS, &link_status);
    if(!link_status)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, link_infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << link_infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    for (GLuint shader : shaders) {
        glDeleteShader(shader);
    }
}


void Shader::use()
{
    glUseProgram(this->Program);
}

void Shader::del() {
    glDeleteProgram(this->Program);
}

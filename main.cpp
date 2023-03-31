#include "sb7.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Shader.h"
#include "vmath.h"

static double PI = acos(-1);

class my_application : public sb7::application {
private:
    Shader * shader;
    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    GLuint index_buffer_object;
    vmath::mat4 proj_matrix;
    float aspect;
    const int mv_location = 1;
    const int proj_location = 2;
    GLfloat vertex_data[3 * 8] = {
            -0.25f,-0.25f,-0.25f,
            -0.25f,0.25f,-0.25f,
            0.25f,-0.25f,-0.25f,
            0.25f,0.25f,-0.25f,
            0.25f,-0.25f,0.25f,
            0.25f,0.25f,0.25f,
            -0.25f,-0.25f,0.25f,
            -0.25f,0.25f,0.25f
    };
    GLushort vertex_indices[3 * 12] = {
            0,1,2,
            2,1,3,
            2,3,4,
            4,3,5,
            4,5,6,
            6,5,7,
            6,7,0,
            0,7,1,
            6,0,2,
            2,4,6,
            7,5,3,
            7,3,1
    };

public:
    void init() override {
        sb7::application::init();
        info.windowHeight = 1080;
        info.windowWidth = 1920;
    }

    void startup() override {
        updateProjMatrix();
        glEnable(GL_DEPTH_TEST);
        ShaderInfo shaders[]{ShaderInfo("vertex_shader.glsl",GL_VERTEX_SHADER),
                             ShaderInfo("fragment_shader.glsl",GL_FRAGMENT_SHADER)/*,
                             ShaderInfo("subdivision_controller.glsl",GL_TESS_CONTROL_SHADER),
                             ShaderInfo("subdivision_evaluator.glsl",GL_TESS_EVALUATION_SHADER),
                             ShaderInfo("geometry_shader.glsl",GL_GEOMETRY_SHADER)*/};
        shader = new Shader(2, shaders);
        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
        glGenBuffers(1,&vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glGenBuffers(1,&index_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);
    };

    void render(double currentTime) override {
        shader->use();
        GLfloat black[] = {0.0,0.0,0.0,1.0};

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(int count = 0;count <= 64;count++) {
            float f = (float)count + (float) currentTime * M_PI * 0.1f;
            vmath::mat4 mv_matrix =
                    vmath::translate(0.0f,0.0f, -10.0f) *
                    vmath::translate(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f,
                                     sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
                    vmath::rotate((float) currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
                    vmath::rotate((float) currentTime * 81.0f, 1.0f, 0.0f, 0.0f);

            glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
            glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
        }
    }

    void shutdown() override {
        shader->del();
        delete shader;
        glDeleteVertexArrays(1, &vertex_array_object);
    }

    void onResize(int w,int h) override {
        sb7::application::onResize(w,h);
        updateProjMatrix();
    }

    void updateProjMatrix(){
        aspect = (float)info.windowWidth / (float)info.windowHeight;
        proj_matrix = vmath::perspective(50.0f,aspect,0.1f,1000.0f);
    }
};

DECLARE_MAIN(my_application);

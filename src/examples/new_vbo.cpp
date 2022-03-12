#include "pch.hpp"
#include "examples/new_vbo.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include <vector>
#include <chrono>
#include <iostream>
#include "stdlib.h"
#include "time.h"

Vbo_Data_Container::Vbo_Data_Container()
{
    this->positions = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,

        0.5f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.0f,

        0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f,

        0.0f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,

        0.0f, 0.5f, 0.5f,
        0.0f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,

        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.5f,
        0.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f,

        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,

        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,
    };
    this->colors = {
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    };
}
New_Vbo_Example::New_Vbo_Example()
{
    this->program = gl_build_program(PATH_TO_VEREX_SHADER, PATH_TO_FRAGMENT_SHADER);
    this->matrix_loc = glGetUniformLocation(this->program, "i_globT");

    this->pos_loc = glGetAttribLocation(this->program, "i_pos");
    this->color_loc = glGetAttribLocation(this->program, "i_color");

    glGenBuffers(1, &this->vbo_indices.positions);
    glGenBuffers(1, &this->vbo_indices.colors);
    glGenBuffers(1, &this->vbo_indices.elements);

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindVertexBuffer(this->position_buffer_binding_point, this->vbo_indices.positions, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->pos_loc, 3, GL_FLOAT, false, 0);
    // glVertexAttribBinding(this->pos_loc, this->position_buffer_binding_point);
    glEnableVertexAttribArray(this->pos_loc);

    glBindVertexBuffer(this->color_buffer_binding_point, this->vbo_indices.colors, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->color_loc, 3, GL_FLOAT, false, 0);
    // glVertexAttribBinding(this->color_loc, this->color_buffer_binding_point);
    glEnableVertexAttribArray(this->color_loc);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_indices.positions);
    glBufferData(GL_ARRAY_BUFFER, this->data_containers.positions.size() * sizeof(float), this->data_containers.positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_indices.colors);
    glBufferData(GL_ARRAY_BUFFER, this->data_containers.colors.size() * sizeof(float), this->data_containers.colors.data(), GL_STATIC_DRAW);

    // NOTE: not mandatory
    glBindVertexArray(0);
}
void New_Vbo_Example::update()
{
    glDisable(GL_CULL_FACE);

    glBindVertexArray(this->vao);
    glBindVertexBuffer(this->position_buffer_binding_point, this->vbo_indices.positions, 0, 3 * sizeof(float));
    glBindVertexBuffer(this->color_buffer_binding_point, this->vbo_indices.colors, 0, 3 * sizeof(float));

    glUseProgram(this->program);
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glm::mat4 view = glm::identity<glm::mat4>();
    glm::mat4 rotated = glm::rotate<glm::f32>(view, (glm::f32)((double)std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0), glm::vec3(0.f, 1.f, 1.f));
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(rotated));
    glDrawArrays(GL_TRIANGLES, 0, this->data_containers.positions.size());
    // glDrawElements()
    // std::cout << "updating" << std::endl;
}
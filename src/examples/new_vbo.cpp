#include "pch.hpp"
#include "examples/new_vbo.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include <vector>
#include "stdlib.h"

Example_Data_Container::Example_Data_Container()
{
    this->positions = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.f};
    this->colors = std::vector<float>{
        0.8f, 0.0f, 0.0f,
        0.0f, 0.8f, 0.0f,
        0.0f, 0.0f, 0.8f};
}
New_Vbo_Example::New_Vbo_Example()
{
    this->program = gl_build_program(PATH_TO_VEREX_SHADER, PATH_TO_FRAGMENT_SHADER);
    this->matrix_loc = glGetUniformLocation(this->program, "i_globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(ortho));

    this->pos_loc = glGetAttribLocation(this->program, "i_pos");
    this->color_loc = glGetAttribLocation(this->program, "i_color");
    glGenBuffers(1, &this->vbo_indices.positions);
    glGenBuffers(1, &this->vbo_indices.colors);

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
}
void New_Vbo_Example::update()
{
    // glDisable(GL_CULL_FACE);
    // glBindVertexBuffer(this->position_buffer_binding_point, this->vbo_indices.positions, 0, 3 * sizeof(float));
    // glBindVertexBuffer(this->color_buffer_binding_point, this->vbo_indices.colors, 0, 3 * sizeof(float));

    // FIXME: magic number 3
    glUseProgram(this->program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements()
    // std::cout << "updating" << std::endl;
}
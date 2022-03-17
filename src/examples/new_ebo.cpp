#include "pch.hpp"
#include "examples/new_ebo.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include <vector>
#include <iostream>
#include <chrono>
#include "stdlib.h"

Ebo_Data_Container::Ebo_Data_Container()
{
    this->positions = {
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f};
    this->colors = std::vector<float>{
        0.8f, 0.0f, 0.0f,
        0.0f, 0.8f, 0.0f,
        0.0f, 0.0f, 0.8f,
        0.8f, 0.8f, 0.8f,
        0.0f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.0f,
        0.8f, 0.0f, 0.8f,
        0.0f, 0.0f, 0.0f};
    this->elements = std::vector<uint32_t>{
        4, 0, 2, 4, 2, 6,
        5, 3, 1, 5, 7, 3,
        7, 2, 3, 7, 6, 2,
        5, 1, 0, 5, 0, 4,
        3, 1, 0, 3, 0, 2,
        7, 5, 4, 7, 4, 6};
}
New_Ebo_Example::New_Ebo_Example()
{
    this->program = gl_build_program(PATH_TO_VEREX_SHADER, PATH_TO_FRAGMENT_SHADER);
    this->matrix_loc = glGetUniformLocation(this->program, "i_globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(ortho));

    this->pos_loc = glGetAttribLocation(this->program, "i_pos");
    this->color_loc = glGetAttribLocation(this->program, "i_color");
    glGenBuffers(1, &this->vao_binding_indices.positions);
    glGenBuffers(1, &this->vao_binding_indices.colors);
    glGenBuffers(1, &this->vao_binding_indices.elements);

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindVertexBuffer(this->position_buffer_binding_point, this->vao_binding_indices.positions, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->pos_loc, 3, GL_FLOAT, false, 0);
    // glVertexAttribBinding(this->pos_loc, this->position_buffer_binding_point);
    glEnableVertexAttribArray(this->pos_loc);

    glBindVertexBuffer(this->color_buffer_binding_point, this->vao_binding_indices.colors, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->color_loc, 3, GL_FLOAT, false, 0);
    // glVertexAttribBinding(this->color_loc, this->color_buffer_binding_point);
    glEnableVertexAttribArray(this->color_loc);

    glBindBuffer(GL_ARRAY_BUFFER, this->vao_binding_indices.positions);
    glBufferData(GL_ARRAY_BUFFER, this->data_containers.positions.size() * sizeof(float), this->data_containers.positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vao_binding_indices.colors);
    glBufferData(GL_ARRAY_BUFFER, this->data_containers.colors.size() * sizeof(float), this->data_containers.colors.data(), GL_STATIC_DRAW);

    // FIXME:
    glVertexArrayElementBuffer(this->vao, this->vao_binding_indices.elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vao_binding_indices.elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->data_containers.elements.size() * sizeof(float), this->data_containers.elements.data(), GL_STATIC_DRAW);

    // NOTE: not mandatory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
auto start_time = (double)std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0;
void New_Ebo_Example::update()
{
    // glDisable(GL_CULL_FACE);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vao_binding_indices.elements);
    glBindVertexBuffer(this->position_buffer_binding_point, this->vao_binding_indices.positions, 0, 3 * sizeof(float));
    glBindVertexBuffer(this->color_buffer_binding_point, this->vao_binding_indices.colors, 0, 3 * sizeof(float));

    glUseProgram(this->program);
    glm::mat4 ortho = glm::ortho(-10.f, (GLfloat)10, (GLfloat)10, -10.f, 1.0f, 1000.f);
    glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.f, 1.f, 1.f));
    glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-0.5f, -0.5f, -0.5f));
    double time = (double)std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0 - start_time;
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(0.f, 1.f, 1.f)));
    glm::mat4 inverse_translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 position_matrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -10.f));
    glm::mat4 final_transform = ortho * (position_matrix * (inverse_translation * (rotation * (translation * scale))));
    // glm::mat4 final_transform = inverse_translation * (rotation * (translation * scale));
    // final_transform = glm::identity<glm::mat4>();
    // final_transform = rotation;

    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(final_transform));
    glDrawElements(GL_TRIANGLES, this->data_containers.elements.size(), GL_UNSIGNED_INT, 0);
    // std::cout << "updating" << std::endl;
}
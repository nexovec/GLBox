#include "examples/new_ebo.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include "main.h"
#include "pch.hpp"
#include "stdlib.h"
#include "utils/utils.hpp"
#include <chrono>
#include <iostream>
#include <vector>

Ebo_Data_Container::Ebo_Data_Container()
{
    populate_unit_cube_vertex_positions(this->positions);
    this->colors = std::vector<float>{
        0.8f, 0.0f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.8f, 0.8f,
        0.0f, 0.8f, 0.8f, 0.8f, 0.8f, 0.0f, 0.8f, 0.0f, 0.8f, 0.0f, 0.0f, 0.0f};
    this->elements = std::vector<uint32_t>{4, 0, 2, 4, 2, 6, 3, 5, 1, 3, 7, 5,
                                           2, 7, 3, 2, 6, 7, 5, 0, 1, 5, 4, 0,
                                           2, 3, 0, 0, 3, 1, 7, 4, 5, 7, 6, 4};
}
New_Ebo_Example::New_Ebo_Example()
{
    this->program =
        gl_build_program(PATH_TO_VEREX_SHADER, PATH_TO_FRAGMENT_SHADER);
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

    glBindVertexBuffer(this->position_buffer_binding_point,
                       this->vao_binding_indices.positions, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->pos_loc, 3, GL_FLOAT, false, 0);
    glEnableVertexAttribArray(this->pos_loc);

    glBindVertexBuffer(this->color_buffer_binding_point,
                       this->vao_binding_indices.colors, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->color_loc, 3, GL_FLOAT, false, 0);
    glEnableVertexAttribArray(this->color_loc);

    glBindBuffer(GL_ARRAY_BUFFER, this->vao_binding_indices.positions);
    glBufferData(GL_ARRAY_BUFFER,
                 this->data_containers.positions.size() * sizeof(float),
                 this->data_containers.positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vao_binding_indices.colors);
    glBufferData(GL_ARRAY_BUFFER,
                 this->data_containers.colors.size() * sizeof(float),
                 this->data_containers.colors.data(), GL_STATIC_DRAW);

    glVertexArrayElementBuffer(this->vao, this->vao_binding_indices.elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vao_binding_indices.elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 this->data_containers.elements.size() * sizeof(float),
                 this->data_containers.elements.data(), GL_STATIC_DRAW);

    // NOTE: not mandatory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
static double start_time = (double)std::chrono::high_resolution_clock::now()
                               .time_since_epoch()
                               .count() /
                           1000000000.0;
static glm::vec3 camera_position = glm::vec3(0.f, 0.f, 0.f);
static float camera_speed = 0.08f;
static float cube_scale_factor = 5.0f;

void New_Ebo_Example::update()
{
    // glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vao_binding_indices.elements);
    glBindVertexBuffer(this->position_buffer_binding_point,
                       this->vao_binding_indices.positions, 0, 3 * sizeof(float));
    glBindVertexBuffer(this->color_buffer_binding_point,
                       this->vao_binding_indices.colors, 0, 3 * sizeof(float));

    glUseProgram(this->program);

    glm::mat4 ortho_m =
        glm::ortho(-10.f, (GLfloat)10, (GLfloat)10, -10.f, 1.0f, 1000.f);
    glm::mat4 cube_scale = glm::scale(
        glm::identity<glm::mat4>(),
        glm::vec3(cube_scale_factor, cube_scale_factor, cube_scale_factor));
    glm::mat4 cube_origin_translation = glm::translate(
        glm::identity<glm::mat4>(), glm::vec3(-0.5f, -0.5f, -0.5f));
    glm::mat4 cube_position =
        glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -10.f));
    glm::mat4 cube_inverse_origin_translation =
        glm::inverse(cube_origin_translation);
    double time =
        std::chrono::high_resolution_clock::now().time_since_epoch().count() /
            1000000000.0 -
        start_time;
    glm::mat4 cube_rotation =
        glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time),
                    glm::normalize(glm::vec3(0.f, 1.f, 1.f)));
    if (get_key_state('W'))
    {
        std::cout << "W pressed!" << std::endl;
        camera_position.y -= camera_speed;
    }
    else if (get_key_state('S'))
    {
        camera_position.y += camera_speed;
    }
    else if (get_key_state('A'))
    {
        camera_position.x -= camera_speed;
    }
    else if (get_key_state('D'))
    {
        camera_position.x += camera_speed;
    }
    glm::mat4 camera_position_m =
        glm::translate(glm::identity<glm::mat4>(), -camera_position);
    glm::mat4 camera_rotation_m =
        glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time),
                    glm::normalize(glm::vec3(0.f, 1.f, 1.f)));
    glm::mat4 final_transform_m = ortho_m * camera_position_m * cube_position *
                                  cube_inverse_origin_translation * cube_scale *
                                  cube_rotation * cube_origin_translation;

    glUniformMatrix4fv(this->matrix_loc, 1, false,
                       glm::value_ptr(final_transform_m));
    glDrawElements(GL_TRIANGLES, this->data_containers.elements.size(),
                   GL_UNSIGNED_INT, 0);

    // NOTE: not mandatory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
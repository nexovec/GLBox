#include "pch.hpp"
#include "examples/uv_test.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include <vector>
#include <iostream>
#include <chrono>
#include "stdlib.h"
#include "main.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define FRAGMENT_PATH "res/shaders/frag_uv.glsl"
#define VERTEX_PATH "res/shaders/vert_uv.glsl"
#define PATH_TO_CUBE_TEXTURE "res/images/wood.jpg"
// #define PATH_TO_CUBE_TEXTURE "res/images/bunga.jpg"

// TODO: integrate, change
Uv_Test_Data_Container::Uv_Test_Data_Container()
{
    this->positions = std::vector<float>{
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f};
    this->tex_coords = std::vector<float>{
        // TODO: probably change this
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f};
    this->elements = std::vector<uint32_t>{2, 0, 1, 1, 3, 2};
}
Uv_Test_Example::Uv_Test_Example()
{
    this->program = gl_build_program(VERTEX_PATH, FRAGMENT_PATH);
    this->matrix_loc = glGetUniformLocation(this->program, "i_globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(ortho));

    this->pos_loc = glGetAttribLocation(this->program, "i_pos");
    this->tex_coord_loc = glGetAttribLocation(this->program, "i_tex_coord");
    glGenBuffers(1, &this->attrib_buffer_indices.positions);
    glGenBuffers(1, &this->attrib_buffer_indices.elements);
    glGenBuffers(1, &this->attrib_buffer_indices.tex_coords);

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindVertexBuffer(this->position_buffer_binding_point, this->attrib_buffer_indices.positions, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->pos_loc, 3, GL_FLOAT, false, 0);
    glEnableVertexAttribArray(this->pos_loc);

    glBindVertexBuffer(this->tex_coords_binding_point, this->attrib_buffer_indices.tex_coords, 0, 3 * sizeof(float));
    glVertexAttribFormat(this->tex_coord_loc, 2, GL_FLOAT, false, 0);
    glEnableVertexAttribArray(this->tex_coord_loc);

    glBindBuffer(GL_ARRAY_BUFFER, this->attrib_buffer_indices.positions);
    glBufferData(GL_ARRAY_BUFFER, this->data_containers.positions.size() * sizeof(float), this->data_containers.positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->attrib_buffer_indices.tex_coords);
    glBufferData(GL_ARRAY_BUFFER, this->data_containers.tex_coords.size() * sizeof(float), this->data_containers.tex_coords.data(), GL_STATIC_DRAW);

    int width{}, height{}, nrChannels{};
    unsigned char *data = stbi_load(PATH_TO_CUBE_TEXTURE, &width, &height, &nrChannels, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &this->texture_id);
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    // TODO: get rid of color attribute
    // FIXME: cube is black, probably texture not bound correctly

    glVertexArrayElementBuffer(this->vao, this->attrib_buffer_indices.elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->attrib_buffer_indices.elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->data_containers.elements.size() * sizeof(float), this->data_containers.elements.data(), GL_STATIC_DRAW);

    // NOTE: not mandatory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
static double start_time = (double)std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0;
static glm::vec3 camera_position = glm::vec3(0.f, 0.f, 0.f);
static float camera_speed = 0.08f;
static float cube_scale_factor = 5.0f;

void Uv_Test_Example::update()
{
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    // glEnable(GL_CULL_FACE);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->attrib_buffer_indices.elements);
    glBindVertexBuffer(this->position_buffer_binding_point, this->attrib_buffer_indices.positions, 0, 3 * sizeof(float));
    glBindVertexBuffer(this->tex_coords_binding_point, this->attrib_buffer_indices.tex_coords, 0, 2 * sizeof(float));
    // glBindTexture(GL_TEXTURE_2D, this->texture_id);
    // glBindTextureUnit(0, this->texture_id);
    glActiveTexture(0);
    glBindTextureUnit(0, this->texture_id);
    glUseProgram(this->program);

    glm::mat4 ortho_m = glm::ortho(-10.f, (GLfloat)10, (GLfloat)10, -10.f, 1.0f, 1000.f);
    glm::mat4 cube_scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(cube_scale_factor, cube_scale_factor, cube_scale_factor));
    glm::mat4 cube_origin_translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-0.5f, -0.5f, -0.5f));
    glm::mat4 cube_position = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -10.f));
    glm::mat4 cube_inverse_origin_translation = glm::inverse(cube_origin_translation);
    double time = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0 - start_time;
    glm::mat4 cube_rotation = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(1.98f, 0.f, 0.f)));
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
    glm::mat4 camera_position_m = glm::translate(glm::identity<glm::mat4>(), -camera_position);
    glm::mat4 camera_rotation_m = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(0.f, 1.f, 1.f)));
    glm::mat4 final_transform_m = ortho_m * camera_position_m * cube_position * cube_inverse_origin_translation * cube_scale * cube_rotation * cube_origin_translation;

    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(final_transform_m));

    glDrawElements(GL_TRIANGLES, this->data_containers.elements.size(), GL_UNSIGNED_INT, 0);

    // NOTE: not mandatory
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
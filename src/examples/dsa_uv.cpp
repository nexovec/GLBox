#include "examples/dsa_uv.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include "main.h"
#include "pch.hpp"
#include "stdlib.h"
#include "utils/utils.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include "stb_image.h"

#define FRAGMENT_PATH "res/shaders/uv.frag"
// #define FRAGMENT_PATH "res/shaders/give_me_tex_coords.frag"
#define VERTEX_PATH "res/shaders/uv.vert"
#define PATH_TO_CUBE_TEXTURE "res/images/wood.jpg"

DSA_Uv_Data_Container::DSA_Uv_Data_Container()
{
    this->positions = std::vector<float>{
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end

        1.0f, 1.0f, -1.0f, // triangle 2 : begin
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, // triangle 2 : end

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};
    // populate_unit_cube_vertex_positions(this->positions);
    this->tex_coords = std::vector<float>{
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f, //

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f, //

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f, //

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f, //

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f, //

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f, //

        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f, //

        1.0f, 0.0f,
        1.0f, 1.0f, //
        0.0f, 1.0f,

        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f, //

        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f, //
    };
    this->elements = std::vector<uint32_t>{
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    // DEBUG:
    glDisable(GL_CULL_FACE);
}
DSA_Uv_Example::DSA_Uv_Example()
{
    this->program =
        gl_build_program(VERTEX_PATH, FRAGMENT_PATH);
    this->matrix_loc = glGetUniformLocation(this->program, "i_globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(ortho));

    this->pos_loc = glGetAttribLocation(this->program, "i_pos");
    this->tex_coords_loc = glGetAttribLocation(this->program, "i_tex_coords");
    glCreateBuffers(1, &this->attrib_buffer_indices.positions);
    glCreateBuffers(1, &this->attrib_buffer_indices.tex_coords);
    glCreateBuffers(1, &this->attrib_buffer_indices.elements);
    glCreateVertexArrays(1, &this->vao);
    glEnableVertexArrayAttrib(this->vao, this->pos_loc);
    glVertexArrayAttribBinding(this->vao, this->attrib_buffer_indices.positions, this->position_buffer_binding_point);
    glVertexArrayAttribFormat(this->vao, this->pos_loc, 3, GL_FLOAT, GL_FALSE, 0);
    glEnableVertexArrayAttrib(this->vao, this->tex_coords_loc);
    glVertexArrayAttribBinding(this->vao, this->attrib_buffer_indices.tex_coords, this->tex_coords_buffer_binding_point);
    glVertexArrayAttribFormat(this->vao, this->tex_coords_loc, 2, GL_FLOAT, GL_FALSE, 0);
    glNamedBufferData(this->attrib_buffer_indices.positions, this->data_containers.positions.size() * sizeof(float), this->data_containers.positions.data(), GL_STATIC_DRAW);
    glNamedBufferData(this->attrib_buffer_indices.tex_coords, this->data_containers.tex_coords.size() * sizeof(float), this->data_containers.tex_coords.data(), GL_STATIC_DRAW);
    // TODO: use index buffer
    int width{}, height{}, nrChannels{};
    unsigned char *data = stbi_load(PATH_TO_CUBE_TEXTURE, &width, &height, &nrChannels, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &this->texture_id);

    glTexParameteri(this->texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(this->texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureStorage2D(this->texture_id, 1, GL_RGB8, width, height);
    glTextureSubImage2D(this->texture_id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(this->texture_id);
    stbi_image_free(data);
    glNamedBufferData(this->attrib_buffer_indices.elements, this->data_containers.elements.size() * sizeof(float), this->data_containers.elements.data(),
                      GL_STATIC_DRAW);
}
static double start_time = (double)std::chrono::high_resolution_clock::now()
                               .time_since_epoch()
                               .count() /
                           1000000000.0;
static glm::vec3 camera_position = glm::vec3(0.f, 0.f, 0.f);
static float camera_speed = 0.08f;
static float cube_scale_factor = 5.0f;

void DSA_Uv_Example::update()
{
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
    glm::mat4 ortho_m = glm::ortho(-10.f, (GLfloat)10, (GLfloat)10, -10.f, 1.0f, 1000.f);
    glm::mat4 cube_scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(cube_scale_factor, cube_scale_factor, cube_scale_factor));
    glm::mat4 cube_origin_translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-0.5f, -0.5f, -0.5f));
    glm::mat4 cube_position = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -10.f));
    glm::mat4 cube_inverse_origin_translation = glm::inverse(cube_origin_translation);
    double time = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0 - start_time;
    glm::mat4 cube_rotation = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(1.0f, 0.3f, 0.1f * time)));
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
    glm::mat4 camera_rotation_m = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(0.f, 0.f, 1.f)));
    glm::mat4 final_transform_m = ortho_m * camera_rotation_m * camera_position_m * cube_position * cube_inverse_origin_translation * cube_scale * cube_rotation * cube_origin_translation;

    glBindVertexArray(this->vao);
    glVertexArrayVertexBuffer(this->vao, this->position_buffer_binding_point, this->attrib_buffer_indices.positions, 0, 3 * sizeof(float));
    glVertexArrayVertexBuffer(this->vao, this->tex_coords_buffer_binding_point, this->attrib_buffer_indices.tex_coords, 0, 2 * sizeof(float));
    glVertexArrayElementBuffer(this->vao, this->attrib_buffer_indices.elements);

    glUseProgram(this->program);
    glBindTextureUnit(0, this->texture_id);
    glUniform1i(glGetUniformLocation(this->program, "our_texture"), 0);

    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(final_transform_m));
    glDrawElements(GL_TRIANGLES, this->data_containers.elements.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, this->data_containers.positions.size() / 3);
}
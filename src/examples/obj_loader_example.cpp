#include "examples/obj_loader_example.hpp"
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
#include "utils/utils.hpp"
#define FAST_OBJ_IMPLEMENTATION
#include "fast_obj.h"

#define FRAGMENT_PATH "res/shaders/uv.frag"
// #define FRAGMENT_PATH "res/shaders/give_me_tex_coords.frag"
#define VERTEX_PATH "res/shaders/uv.vert"
#define PATH_TO_CUBE_TEXTURE "res/images/wood.jpg"
#define PATH_TO_CUBE_TEXTURE "res/models/_ignored/terrain/textures/diff2.jpg"
#define PATH_TO_OBJ_MODEL "res/models/cube/cube.obj"
// #define PATH_TO_OBJ_MODEL "res/models/_ignored/car/car.obj"
#define PATH_TO_OBJ_MODEL "res/models/_ignored/terrain/source/terrain.obj"

extern double mouse_xpos, mouse_ypos;
double start_mouse_xpos, start_mouse_ypos;

OBJ_Loader_Data_Container::OBJ_Loader_Data_Container()
{
    File_Container obj_file = read_file((const char *)PATH_TO_OBJ_MODEL);
    fastObjMesh *obj_model = fast_obj_read(PATH_TO_OBJ_MODEL);

    // TODO: operate on obj_model
    if (!obj_model)
    {
        std::cerr << "obj_loader_example failed to parse obj model: " << PATH_TO_OBJ_MODEL << std::endl;
        terminate();
    }
    this->positions = std::vector<float>();
    this->tex_coords = std::vector<float>();
    this->normals = std::vector<float>();
    this->elements = std::vector<uint32_t>();
    size_t index_count = obj_model->index_count;
    for (uint32_t i = 0; i < index_count; i++)
    {
        auto current_element = obj_model->indices[i];
        this->positions.push_back(obj_model->positions[current_element.p * 3 + 0]);
        this->positions.push_back(obj_model->positions[current_element.p * 3 + 1]);
        this->positions.push_back(obj_model->positions[current_element.p * 3 + 2]);
        this->normals.push_back(obj_model->normals[current_element.n * 3 + 0]);
        this->normals.push_back(obj_model->normals[current_element.n * 3 + 1]);
        this->normals.push_back(obj_model->normals[current_element.n * 3 + 2]);
        this->tex_coords.push_back(obj_model->texcoords[current_element.t * 2 + 0]);
        this->tex_coords.push_back(obj_model->texcoords[current_element.t * 2 + 1]);
        this->elements.push_back(i);
    }
    fast_obj_destroy(obj_model);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    start_mouse_xpos = mouse_xpos;
    // DEBUG:
    // glDisable(GL_CULL_FACE);
}

static glm::mat4 camera_rotation;
static glm::mat4 camera_position;

OBJ_Loader_Example::OBJ_Loader_Example()
{
    this->program =
        gl_build_program(VERTEX_PATH, FRAGMENT_PATH);
    this->matrix_loc = glGetUniformLocation(this->program, "i_globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(ortho));

    this->pos_loc = glGetAttribLocation(this->program, "i_pos");
    this->tex_coords_loc = glGetAttribLocation(this->program, "i_tex_coords");
    glCreateBuffers(1, &this->attrib_buffer_indices.positions);
    glCreateBuffers(1, &this->attrib_buffer_indices.normals);
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
    glVertexArrayVertexBuffer(this->vao, this->position_buffer_binding_point, this->attrib_buffer_indices.positions, 0, 3 * sizeof(float));
    glVertexArrayVertexBuffer(this->vao, this->tex_coords_buffer_binding_point, this->attrib_buffer_indices.tex_coords, 0, 2 * sizeof(float));
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

    camera_rotation = glm::identity<glm::mat4>();
    camera_position = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -10.f));
}
static double start_time = (double)std::chrono::high_resolution_clock::now()
                               .time_since_epoch()
                               .count() /
                           1000000000.0;
static float camera_speed = 1.5f;
static float cube_scale_factor = 0.1f;
static glm::vec3 camera_direction = glm::vec3(0.0f, 0.0f, -1.0f);

void OBJ_Loader_Example::update()
{
    // glm::mat4 ortho_m = glm::ortho(-10.f, (GLfloat)10, (GLfloat)10, -10.f, 0.1f, 100.f);
    glm::mat4 ortho_m = glm::perspective(45.0f, (GLfloat)4 / 3, 0.1f, 300.0f);
    glm::mat4 cube_scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(cube_scale_factor, cube_scale_factor, cube_scale_factor));
    glm::mat4 cube_origin_translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-0.5f, -0.5f, -0.5f));
    glm::mat4 cube_position = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -70.f));
    glm::mat4 cube_inverse_origin_translation = glm::inverse(cube_origin_translation);
    double time = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0 - start_time;
    glm::mat4 model_rotation = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(1.0f, 0.3f, 0.1f * time)));
    model_rotation = glm::identity<glm::mat4>();
    glm::mat4 camera_movement_translation = glm::identity<glm::mat4>();
    if (get_key_state('W'))
    {
        // std::cout << "W pressed!" << std::endl;
        camera_movement_translation = glm::translate(camera_movement_translation, glm::vec3(0.0f, 0.0f, -1.0f * camera_speed));
    }
    if (get_key_state('S'))
    {
        camera_movement_translation = glm::translate(camera_movement_translation, glm::vec3(0.0f, 0.0f, 1.0f * camera_speed));
    }
    // glm::mat4 camera_rotation_m = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(time), glm::normalize(glm::vec3(0.f, 0.f, 1.f)));
    // camera_rotation_m = glm::identity<glm::mat4>();
    // TODO: cleanup
    glm::mat4 camera_rotation_x = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(mouse_xpos - start_mouse_xpos), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 camera_rotation_y = glm::rotate(glm::identity<glm::mat4>(), (glm::f32)(mouse_ypos - start_mouse_ypos), glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotation_y = glm::inverse(camera_rotation_x) * camera_rotation_y * camera_rotation_x;
    // camera_rotation = camera_rotation_x * camera_rotation_y;
    camera_rotation = camera_rotation_x * camera_rotation_y;
    camera_position *= glm::inverse(camera_rotation) * camera_movement_translation * camera_rotation;

    glm::mat4 final_transform_m = ortho_m * camera_rotation * camera_position * cube_position * cube_inverse_origin_translation * cube_scale * model_rotation * cube_origin_translation;
    // DEBUG:
    // final_transform_m = ortho_m * camera_position_m * cube_position * cube_inverse_origin_translation * cube_scale * model_rotation * cube_origin_translation;

    glBindVertexArray(this->vao);
    glVertexArrayElementBuffer(this->vao, this->attrib_buffer_indices.elements);

    glUseProgram(this->program);
    glBindTextureUnit(0, this->texture_id);
    glUniform1i(glGetUniformLocation(this->program, "our_texture"), 0);

    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(final_transform_m));
    glDrawElements(GL_TRIANGLES, (GLsizei)this->data_containers.elements.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, this->data_containers.positions.size() / 3);
}
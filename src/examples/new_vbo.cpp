#include "pch.hpp"
#include "examples/new_vbo.hpp"
#include "utils/utils.hpp"
#include "glad/glad.h"
#include "glm/ext.hpp"
#include <vector>
#include "stdlib.h"

Example_Data_Container::Example_Data_Container()
{
    // FIXME: magic numbers EVERYWHERE
    this->positions = (float *)malloc(9 * sizeof(float));
    this->colors = (float *)malloc(9 * sizeof(float));

    float p[] = {
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,
    };
    memcpy(this->positions, p, 9 * sizeof(float));
    for (int i = 0; i < 9; i++)
    {
        colors[i] = 1.0f;
    }
    std::cout << "data container spawned." << std::endl;
}
Example_Data_Container::~Example_Data_Container()
{
    free(this->positions);
    free(this->colors);
    std::cout << "data container Destructed." << std::endl;
}
New_Vbo_Example::New_Vbo_Example()
{
    this->program = gl_build_program(PATH_TO_VEREX_SHADER, PATH_TO_FRAGMENT_SHADER);
    this->matrix_loc = glGetUniformLocation(this->program, "globT");
    glm::mat4 ortho = glm::ortho(0.f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.f, 0.f, 1000.f);
    glUniformMatrix4fv(this->matrix_loc, 1, false, glm::value_ptr(ortho));

    this->pos_loc = glGetAttribLocation(this->program, "pos");
    this->color_loc = glGetAttribLocation(this->program, "color");

    // std::cout << this->color_loc << std::endl;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // NOTE: I don't know what the difference between offset in glAttribPointer and glBindVertexBuffer is
    glVertexAttribPointer(this->pos_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glVertexAttribBinding(this->pos_loc, this->position_buffer_binding_point);

    // FIXME: crashes:
    glEnableVertexAttribArray(this->pos_loc);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(this->color_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)(3 * sizeof(float)));
    glVertexAttribPointer(this->color_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glVertexAttribBinding(this->color_loc, this->color_buffer_binding_point);

    // FIXME: crashes:
    glEnableVertexAttribArray(this->color_loc);
    // glEnableVertexAttribArray(1);

    glGenBuffers(1, &this->vbo_indices.positions);
    glGenBuffers(1, &this->vbo_indices.colors);

    // FIXME: magic numbers
    glBindBuffer(GL_ARRAY_BUFFER,this->vbo_indices.positions);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), this->data_containers.positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_indices.colors);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), this->data_containers.colors, GL_STATIC_DRAW);
}
void New_Vbo_Example::update()
{
    glDisable(GL_CULL_FACE);
    glBindVertexBuffer(this->position_buffer_binding_point, this->vbo_indices.positions, 0, 3 * sizeof(float));
    glBindVertexBuffer(this->color_buffer_binding_point, this->vbo_indices.colors, 0, 3 * sizeof(float));

    // FIXME: magic number 3
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements()
    // std::cout << "updating" << std::endl;
}
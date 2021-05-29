#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLuint make_shader(GLenum type, const char *const shader_src);
GLuint load_shader(GLenum type, const char *const shader_path);
GLuint load_program(const char *const vshader_path,
                    const char *const fshader_path);

void shaderSetFloat(GLuint program, const char *const name, float num);
void shaderSetInt(GLuint program, const char *const name, GLuint num);
void shaderSetVec3(GLuint program, const char *const name, float *vec);
void shaderSetMat4(GLuint program, const char *const name, float *mat);

#endif

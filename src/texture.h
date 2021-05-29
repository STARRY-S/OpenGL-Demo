#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

GLuint load_texture(const char *const path, int format);

#endif

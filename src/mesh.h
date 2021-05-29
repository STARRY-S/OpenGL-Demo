#ifndef __MESH_H__
#define __MESH_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/call.h>

struct Vertex {
        vec3 Position;
        vec3 Normal;
        vec2 TexCoords;
};

struct Texture {
        unsigned int id;
        char *type;
};

struct Mesh {
        struct Vertex *vertices;
        uint32_t indices;
        struct Texture *textures;
};

#endif

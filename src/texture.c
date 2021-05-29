#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint load_texture(const char *const path, int format)
{
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        // stbi_set_flip_vertically_on_load(true);
        unsigned char *data = NULL;
        data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
                // target, level, format,
                // w, h, 0(always), origin_format,
                // data_format, data
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                             width, height, 0, format,
                             GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
        } else {
                fprintf(stderr, "Failed to load texture: %s\n", path);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);

        return texture;
}

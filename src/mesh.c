#include "mesh.h"
#include <stdlib.h>

#define VERTEX_SIZE 100
#define TEXTURE_SIZE 100

typedef struct Mesh SM;
typedef struct Vertex SV;
typedef struct Texture ST;

void initMesh(struct Mesh *mesh)
{
        mesh->vertices = (SV*) malloc(VERTEX_SIZE * sizeof(SV));
        if (mesh == NULL) {
                fprintf(stderr, "Malloc error.\n");
                return;
        }
}

void setupMesh()
{
        ;
}

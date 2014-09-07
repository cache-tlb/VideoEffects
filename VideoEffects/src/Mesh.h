#ifndef MESH_H
#define MESH_H

#include "common.h"
#include "glheader.h"
#include "VSL/vsShaderLib.h"
#include "vec3.h"

class Mesh {
public:
    Mesh();

    GLuint vao;
    GLuint vertex_coord_buff, texture_coord_buff, normal_buff, tri_index_buff;

    bool hasCoords, hasNormals;

    std::vector<float> vertices;    // x, y, z
    std::vector<float> texture_coords;      // x, y
    std::vector<float> normals;     // x, y, z
    std::vector<unsigned int> triangles;    // i, j, k

    void compile();

    static Mesh *plane(int detailX = 1, int detailY = 1);
protected:
private:
};


#endif // MESH_H

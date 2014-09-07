#include "Mesh.h"


Mesh::Mesh(): 
    hasCoords(true), hasNormals(false),
    vao(-1), vertex_coord_buff(-1), texture_coord_buff(-1), normal_buff(-1), tri_index_buff(-1)
{
    // TODO
}

void Mesh::compile() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertex_coord_buff);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_coord_buff);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
    glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 3, GL_FLOAT, 0, 0, 0);  // note: it is 3 for xyz !

    if (hasCoords) {
        glGenBuffers(1, &texture_coord_buff);
        glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buff);
        glBufferData(GL_ARRAY_BUFFER, texture_coords.size() * sizeof(float), &texture_coords[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
        glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);
    }

    if (hasNormals) {
        glGenBuffers(1, &normal_buff);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buff);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
        glVertexAttribPointer(VSShaderLib::NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
    }

    glGenBuffers(1, &tri_index_buff);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_index_buff);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &triangles[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

}

Mesh *Mesh::plane(int detailX /* = 1 */, int detailY /* = 1 */) {
    Mesh *mesh = new Mesh();
    for (int y = 0; y <= detailY; y++) {
        float t = (float)y / (float)detailY;
        for (int x = 0; x <= detailX; x++) {
            float s = (float)x / (float)detailX;
            mesh->vertices.push_back(2.f * s - 1.f);
            mesh->vertices.push_back(2.f * t - 1.f);
            mesh->vertices.push_back(0.f);
            // texture coords
            mesh->texture_coords.push_back(s);
            mesh->texture_coords.push_back(t);
            // normals
            mesh->normals.push_back(0.f);
            mesh->normals.push_back(0.f);
            mesh->normals.push_back(1.f);
            if (x < detailX && y < detailY) {
                int i = x + y * (detailX + 1);
                mesh->triangles.push_back(i);
                mesh->triangles.push_back(i + 1);
                mesh->triangles.push_back(i + detailX + 1);
                mesh->triangles.push_back(i + detailX + 1);
                mesh->triangles.push_back(i + 1);
                mesh->triangles.push_back(i + detailX + 2);
            }
        }
    }
    mesh->compile();
    return mesh;
}




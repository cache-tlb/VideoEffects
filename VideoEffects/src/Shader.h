#ifndef SHADER_H
#define SHADER_H

#include "common.h"
#include "glheader.h"
#include "VSL/vsShaderLib.h"
#include "Mesh.h"
#include "Texture.h"

class Shader{
public:
    // now the vertex and fragment source mean the file path
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
    ~Shader();

    //GLuint program;
    VSShaderLib vsshader;

    void draw(Mesh *mesh);
    
    // before using renderTo, the uniforms should be set first.
    //void renderTo(Mesh *mesh, Texture *texture);

    void uniforms(const std::string &name, void *val);
    void uniforms(const std::string &name, float val);
    void uniforms(const std::string &name, int val);

private:
};

#endif // SHADER_H

#include "Shader.h"
#include "VSL/vsMathLib.h"

extern VSMathLib *vsml;

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
    vsshader.init();
    vsshader.loadShader(VSShaderLib::VERTEX_SHADER, vertexSource);
    vsshader.loadShader(VSShaderLib::FRAGMENT_SHADER, fragmentSource);
    vsshader.setProgramOutput(0,"outputF");

    vsshader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
    vsshader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "uv");
    vsshader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");

    vsshader.prepareProgram();

}

void Shader::draw(Mesh *mesh) {
    // set the uniforms
    glUseProgram(vsshader.getProgramIndex());
    vsml->setUniformName(VSMathLib::NORMAL, "normal_matrix");
    vsml->setUniformName(VSMathLib::VIEW_MODEL, "model_view_matrix");
    vsml->setUniformName(VSMathLib::PROJECTION, "projection_matrix");
    vsml->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "model_view_projection_matrix");
    vsml->matricesToGL();
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->triangles.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/*void Shader::renderTo(Mesh *mesh, Texture *texture) {
    std::function<void(void)> callback = [this, mesh]() {
        this->draw(mesh);
    };
    texture->drawTo(callback);
}*/

void Shader::uniforms(const std::string &name, void *val) {
    glUseProgram(vsshader.getProgramIndex());
    vsshader.setUniform(name, val);
}

void Shader::uniforms(const std::string &name, float val) {
    glUseProgram(vsshader.getProgramIndex());
    vsshader.setUniform(name, val);
}

void Shader::uniforms(const std::string &name, int val) {
    glUseProgram(vsshader.getProgramIndex());
    vsshader.setUniform(name, val);
}

Shader::~Shader() {}

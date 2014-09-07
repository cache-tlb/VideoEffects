#ifndef EFFECTCOMPOSER_H
#define EFFECTCOMPOSER_H

#include "Shader.h"
#include "Texture.h"
#include "VideoTexture.h"

class EffectComposer {
public:
    EffectComposer();
    ~EffectComposer();

    Mesh *planeMesh;

    Texture *readBuffer;
    Texture *writeBuffer;
    VideoTexture *videoTexture;

    Shader *badTVShader;
    Shader *rgbShiftShader;
    Shader *filmShader;
    Shader *staticShader;
    Shader *copyShader;

    float shaderTime;

    void render(float delta);
    void setVideo(VideoTexture *video);

protected:
    void batTVPass();
    void rgbShiftPass();
    void filmPass();
    void staticPass();

private:
};

#endif // EFFECTCOMPOSER_H
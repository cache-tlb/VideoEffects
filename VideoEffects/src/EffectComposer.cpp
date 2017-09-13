#include "EffectComposer.h"

EffectComposer::EffectComposer() {
    Option options;

    planeMesh = Mesh::plane();

    badTVShader = new Shader("./shaders/default.vert", "./shaders/badtv.frag");
    rgbShiftShader = new Shader("./shaders/default.vert", "./shaders/rgbshift.frag");
    filmShader = new Shader("./shaders/default.vert", "./shaders/film.frag");
    staticShader = new Shader("./shaders/default.vert", "./shaders/static.frag");
    copyShader = new Shader("./shaders/default.vert", "./shaders/copy.frag");

    readBuffer = NULL;
    writeBuffer = NULL;

    shaderTime = 0.f;
}

EffectComposer::~EffectComposer() {
    if (planeMesh) delete planeMesh;

    if (readBuffer) delete readBuffer;
    if (writeBuffer) delete writeBuffer;

    if (badTVShader) delete badTVShader;
    if (rgbShiftShader) delete rgbShiftShader;
    if (filmShader) delete filmShader;
    if (staticShader) delete staticShader;
    if (copyShader) delete copyShader;
} 

void EffectComposer::setVideo(VideoTexture *video) {
    videoTexture = video;

    if (readBuffer) delete readBuffer;
    if (writeBuffer) delete writeBuffer;

    Option option;
    option["wrap"] = toString(GL_REPEAT);
    readBuffer = new Texture(video->width, video->height, option);
    writeBuffer = new Texture(video->width, video->height, option);
}

void EffectComposer::render(float delta) {
    // load the video to the read buffer
    videoTexture->updateFrame();
    shaderTime += delta;

    std::function<void(void)> callback = [this](){
        glClear(GL_COLOR_BUFFER_BIT);
        videoTexture->bind(0);
        copyShader->uniforms("tDiffuse", 0);
        copyShader->uniforms("flipY", 0);
        copyShader->uniforms("opacity", 1.0f);
        copyShader->draw(planeMesh);
    };

    writeBuffer->drawTo(callback);
    writeBuffer->swapWith(readBuffer);

    // apply the shader passes
    filmPass();
    batTVPass();
    rgbShiftPass();
    staticPass();
    // render to screen
    readBuffer->bind(0);
    copyShader->uniforms("tDiffuse", 0);
    copyShader->uniforms("flipY", 1);
    copyShader->uniforms("opacity", 1.0f);
    copyShader->draw(planeMesh);
}

void EffectComposer::batTVPass() {
    std::function<void(void)> callback = [this](){
        glClear(GL_COLOR_BUFFER_BIT);
        readBuffer->bind(0);
        badTVShader->uniforms("tDiffuse", 0);
        badTVShader->uniforms("time", shaderTime);
        badTVShader->uniforms("distortion", 2.1f);
        badTVShader->uniforms("distortion2", 7.7f);
        badTVShader->uniforms("speed", 0.32f);
        badTVShader->uniforms("rollSpeed", 0.11f);
        badTVShader->draw(planeMesh);
    };

    writeBuffer->drawTo(callback);
    writeBuffer->swapWith(readBuffer);
}

void EffectComposer::rgbShiftPass() {
    std::function<void(void)> callback = [this](){
        glClear(GL_COLOR_BUFFER_BIT);
        readBuffer->bind(0);
        rgbShiftShader->uniforms("tDiffuse", 0);
        rgbShiftShader->uniforms("amount", 0.0113f);
        rgbShiftShader->uniforms("angle", 1.f);
        rgbShiftShader->draw(planeMesh);
    };

    writeBuffer->drawTo(callback);
    writeBuffer->swapWith(readBuffer);
}

void EffectComposer::filmPass() {
    std::function<void(void)> callback = [this](){
        glClear(GL_COLOR_BUFFER_BIT);
        readBuffer->bind(0);
        filmShader->uniforms("tDiffuse", 0);
        filmShader->uniforms("time", shaderTime);
        filmShader->uniforms("nIntensity", 0.4f);
        filmShader->uniforms("sIntensity", 0.9f);
        filmShader->uniforms("sCount", 800.0f);
        filmShader->uniforms("grayscale", 0);
        filmShader->draw(planeMesh);
    };

    writeBuffer->drawTo(callback);
    writeBuffer->swapWith(readBuffer);
}

void EffectComposer::staticPass() {
    std::function<void(void)> callback = [this](){
        glClear(GL_COLOR_BUFFER_BIT);
        readBuffer->bind(0);
        staticShader->uniforms("tDiffuse", 0);
        staticShader->uniforms("time", shaderTime);
        staticShader->uniforms("amount", 0.17f);
        staticShader->uniforms("size", 2.0f);
        staticShader->draw(planeMesh);
    };

    writeBuffer->drawTo(callback);
    writeBuffer->swapWith(readBuffer);
}

//
// Lighthouse3D.com GLSL Core Tutorial - Hello World Example
//
//
// This demo was built for learning purposes only.
// Some code could be severely optimised, but I tried to
// keep as simple and clear as possible.
//
// The code comes with no warranties, use it at your own risk.
// You may use it, or parts of it, wherever you want.
//
// If you do use it I would love to hear about it. Just post a comment
// at Lighthouse3D.com
#include "common.h"
#include "glheader.h"
#include "VSL/VSMathlib.h"
#include "VSL/VSShaderlib.h"
#include "Shader.h"
#include "Mesh.h"
#include "vec3.h"
#include "Texture.h"
#include "VideoTexture.h"
#include "EffectComposer.h"

VSMathLib *vsml;

// shader and mesh is for test
Shader *shader;
Mesh *mesh;
// -- end test
EffectComposer *composer;
VideoTexture *videoTexture;

// the Water begin

int winWidth, winHeight;
bool paused = false;
int prevTime;

void resize(int w, int h) {
    float fov;
    // Prevent a divide by zero, when window is too short
    if(h == 0) h = 1;
    // set the viewport to be the entire window
    glViewport(0, 0, w, h);
    winWidth = w;
    winHeight = h;
    // set the projection matrix
    fov = (1.0f * w) / h;
    vsml->loadIdentity(VSMathLib::PROJECTION);
    vsml->perspective(45.f, fov, 0.1f, 100.0f);
}

void update(float seconds) {
}


void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vsml->loadIdentity(VSMathLib::VIEW);
    vsml->loadIdentity(VSMathLib::MODEL);
//    videoTexture->updateFrame();
//     videoTexture->bind(0);
//     shader->uniforms("tDiffuse", 0);
//     shader->uniforms("opacity", 1.0f);
//     shader->draw(mesh);
    composer->render(0.1);
    glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
    switch(key) {
    case 27:
        glutLeaveMainLoop();
        break;
    case ' ':
        paused = !paused;
        break;
    default:
        break;
    }

}

void onMouseMove(int x, int y){
}

void onMouseDown(int x, int y) {
}

void onMouseUp(int x, int y) {
} 

void processMouseButtons(int button, int state, int xx, int yy) {
    // start tracking the mouse
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)  {
        onMouseDown(xx, yy);
    }
    else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
        onMouseUp(xx, yy);
    }
}

// Track mouse motion while buttons are pressed

void processMouseMotion(int xx, int yy) {
    onMouseMove(xx, yy);
}

void initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void initVSL() {
    vsml = VSMathLib::getInstance();
    // remove the code below
    //shader = new Shader("shaders/default.vert", "shaders/copy.frag");
    //mesh = Mesh::plane();
}

void initScene(int argc, char** argv) {
    prevTime = glutGet(GLUT_ELAPSED_TIME);
    videoTexture = VideoTexture::fromFile(std::string(argc < 2 ? "./data/fits.mp4" : argv[1]));
    composer = new EffectComposer();
    composer->setVideo(videoTexture);
}


void idle(){
    int nextTime = glutGet(GLUT_ELAPSED_TIME);
    float interval = float(nextTime - prevTime) / 1000.f;
    if (interval < 1./30.) return;
    if (!paused) {
        update(interval);
        draw();
    }
    prevTime = nextTime;
}


int main(int argc, char **argv) {

    //  GLUT initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE);

    glutInitContextVersion (3, 3);
    glutInitContextProfile (GLUT_CORE_PROFILE );
    //glutInitContextFlags(GLUT_DEBUG);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(540,360);
    glutCreateWindow("Lighthouse3D - Simple Shader Demo");

    //  Callback Registration
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    //	Mouse and Keyboard Callbacks
    glutKeyboardFunc(processKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);


    //	return from main loop
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    //	Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    printf ("Vendor: %s\n", glGetString (GL_VENDOR));
    printf ("Renderer: %s\n", glGetString (GL_RENDERER));
    printf ("Version: %s\n", glGetString (GL_VERSION));
    printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

    initOpenGL();

    initVSL();
    initScene(argc, argv);

    //  GLUT main loop
    glutMainLoop();

    return(0);

}

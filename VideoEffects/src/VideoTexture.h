#ifndef VIDEOTEXTURE_H
#define VIDEOTEXTURE_H

#include "common.h"
#include "glheader.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"

class VideoTexture {
public:
    VideoTexture(int w, int h, cv::VideoCapture &_cap);
    ~VideoTexture();

    void bind(int unit = 0);
    void unbind(int unit = 0);

    void play();
    void updateFrame();

    static VideoTexture *fromFile(const std::string &path);

    GLuint textureId;
    GLuint pboIds[2];

    int width, height, dataSize;
    cv::Mat videoFrame;
    //cv::Mat texuterData;
    clock_t timeStamp;   // time when play() is called.
    cv::VideoCapture cap;
protected:
private:
};

#endif // VIDEOTEXTURE_H

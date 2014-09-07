#include "VideoTexture.h"

VideoTexture::VideoTexture(int w, int h, cv::VideoCapture &_cap) 
    : width(w), height(h), cap(_cap), timeStamp(clock()), dataSize(w*h*3)
{
    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // format is GL_RGB
    // type is GL_UNSIGNED_BYTE;

    /*glGenBuffersARB(2, pboIds);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboIds[0]);
    glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, dataSize, 0, GL_STREAM_DRAW_ARB);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboIds[1]);
    glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, dataSize, 0, GL_STREAM_DRAW_ARB);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
    */
}

VideoTexture::~VideoTexture() {}

void VideoTexture::play() {
    timeStamp = clock();
}

void VideoTexture::bind(int unit /* = 0 */) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void VideoTexture::unbind(int unit /* = 0 */) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void VideoTexture::updateFrame() {
    clock_t currentTime = clock();
    double elapsed_secs = double(currentTime - timeStamp) / CLOCKS_PER_SEC;
    double frame_ms = cap.get(CV_CAP_PROP_POS_MSEC);
    bool refreshed = false;
    while (elapsed_secs*1000.0 > frame_ms){
        refreshed = true;
        if (cap.get(CV_CAP_PROP_POS_FRAMES) == cap.get(CV_CAP_PROP_FRAME_COUNT)) {
            cap.set(CV_CAP_PROP_POS_FRAMES, 0.0);
            timeStamp = currentTime;
            elapsed_secs = 0;
        }
        cap.read(videoFrame);
        frame_ms = cap.get(CV_CAP_PROP_POS_MSEC);
    }
    if (refreshed) { 
        cv::cvtColor(videoFrame, videoFrame, CV_BGR2RGB);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, videoFrame.data);
    }
}

VideoTexture *VideoTexture::fromFile(const std::string &path) {
    cv::VideoCapture cap(path);
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH), height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoTexture *texture = new VideoTexture(width, height, cap);

    return texture;
}


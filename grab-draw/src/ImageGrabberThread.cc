#include "ImageGrabberThread.hh"

ImageGrabberThread::ImageGrabberThread(Pylon::CInstantCamera* c) { camera_ = c; }

ImageGrabberThread::~ImageGrabberThread() {}

void ImageGrabberThread::run() {
    //
}
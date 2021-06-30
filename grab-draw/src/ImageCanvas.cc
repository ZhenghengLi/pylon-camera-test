#include "ImageCanvas.hh"
#include <iostream>

ImageCanvas::ImageCanvas(QWidget* parent) : QWidget(parent) {
    //
}

ImageCanvas::~ImageCanvas() {
    //
}

void ImageCanvas::drawImage(QImage image) {
    currentImage_ = image;
    std::cout << "draw image with first pixel: " << image.pixelIndex(0, 0) << std::endl;
}
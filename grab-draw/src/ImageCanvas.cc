#include "ImageCanvas.hh"
#include <iostream>
#include <QPainter>
#include <QPixmap>

ImageCanvas::ImageCanvas(QWidget* parent) : QWidget(parent) {
    //
    resize(500, 500);
}

ImageCanvas::~ImageCanvas() {
    //
}

void ImageCanvas::drawImage(QImage image) {
    currentImage_ = image;
    if (currentImage_.width() < 1) return;

    // std::cout << "draw image with first pixel: " << image.pixelIndex(0, 0) << std::endl;
    // std::cout << image.width() << ", " << image.height() << std::endl;
    // float ratio = 0.5;
    // resize(image.width() * ratio, image.height() * ratio);

    update();
}

void ImageCanvas::paintEvent(QPaintEvent* event) {
    // std::cout << "paint image" << std::endl;
    QPainter painter(this);
    for (size_t i = 0; i < currentImage_.colorCount(); i++) {
        currentImage_.setColor(i, qRgb(i, i, i));
    }
    QPixmap pixmap = QPixmap::fromImage(currentImage_);
    if (pixmap.width() < 1) return;

    int width(0), height(0);
    int owidth(0), oheight(0);

    double win_ratio = (double)this->height() / (double)this->width();
    double pix_ratio = (double)pixmap.height() / (double)pixmap.width();

    if (win_ratio > pix_ratio) {
        width = this->width();
        height = width * pix_ratio;
        oheight = (this->height() - height) / 2;
    } else {
        height = this->height();
        width = height / pix_ratio;
        owidth = (this->width() - width) / 2;
    }

    painter.drawPixmap(owidth, oheight, width, height, pixmap);
}
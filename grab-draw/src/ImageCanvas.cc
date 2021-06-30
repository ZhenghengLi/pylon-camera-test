#include "ImageCanvas.hh"
#include <iostream>
#include <QPainter>
#include <QPixmap>

ImageCanvas::ImageCanvas(QWidget* parent) : QWidget(parent) {
    //
}

ImageCanvas::~ImageCanvas() {
    //
}

void ImageCanvas::drawImage(QImage image) {
    currentImage_ = image;
    if (currentImage_.width() < 1) return;
    // std::cout << "draw image with first pixel: " << image.pixelIndex(0, 0) << std::endl;
    // std::cout << image.width() << ", " << image.height() << std::endl;
    float ratio = 0.5;
    resize(image.width() * ratio, image.height() * ratio);

    update();
}

void ImageCanvas::paintEvent(QPaintEvent* event) {
    // std::cout << "paint image" << std::endl;
    QPainter painter(this);
    for (size_t i = 0; i < currentImage_.colorCount(); i++) {
        currentImage_.setColor(i, qRgb(i, i, i));
    }
    QPixmap pixmap = QPixmap::fromImage(currentImage_);

    // painter.fillRect(0, 0, this->width(), this->height(), Qt::white);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}
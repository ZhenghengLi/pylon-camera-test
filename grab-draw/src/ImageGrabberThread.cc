#include "ImageGrabberThread.hh"
#include <iostream>
#include <QtGlobal>
#include <QDebug>
#include <iostream>

using namespace std;

ImageGrabberThread::ImageGrabberThread(QObject* parent) : QThread(parent) {
    run_flag_ = false;
    camera_ = nullptr;
}

ImageGrabberThread::~ImageGrabberThread() { stopGrabbing(); }

void ImageGrabberThread::run() {
    if (camera_ == nullptr) return;
    try {
        cout << "grabbing ..." << endl;
        doGrabbing_();
        cout << "grabbing finished." << endl;
    } catch (const Pylon::GenericException& e) {
        qCritical() << "Pylon Error 3: " << e.GetDescription();
    } catch (const std::exception& e) {
        qCritical() << "Error: " << e.what();
    }
}

void ImageGrabberThread::doGrabbing_() {
    if (camera_ == nullptr) return;

    camera_->StartGrabbing();

    Pylon::CGrabResultPtr ptrGrabResult;

    while (run_flag_ && camera_->IsGrabbing()) {
        camera_->RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_Return);
        //
        if (ptrGrabResult->GrabSucceeded()) {
            // Access the image data.
            // std::cout << "SizeX: " << ptrGrabResult->GetWidth() << std::endl;
            // std::cout << "SizeY: " << ptrGrabResult->GetHeight() << std::endl;
            // std::cout << "PayloadType: " << ptrGrabResult->GetPayloadType() << std::endl;
            // std::cout << "PixelType: " << std::hex << ptrGrabResult->GetPixelType() << std::dec << std::endl;
            // std::cout << "BufferSize: " << ptrGrabResult->GetBufferSize() << std::endl;

            // size_t stride = 0;
            // ptrGrabResult->GetStride(stride);
            // std::cout << "stride: " << stride << endl;

            QImage image(ptrGrabResult->GetWidth(), ptrGrabResult->GetHeight(), QImage::Format_Indexed8);

            if (ptrGrabResult->GetPixelType() == Pylon::PixelType_Mono12packed) {
                // std::cout << "type: Mono12Packed" << endl;
                emit imageGrabbed(grab2image_mono12packed(ptrGrabResult));
            } else if (ptrGrabResult->GetPixelType() == Pylon::PixelType_Mono12) {
                // cout << "type: Mono12" << endl;
                emit imageGrabbed(grab2image_mono12(ptrGrabResult));
            } else if (ptrGrabResult->GetPixelType() == Pylon::PixelType_Mono8) {
                // cout << "type: Mono8" << endl;
                emit imageGrabbed(grab2image_mono8(ptrGrabResult));
            }

        } else {
            qCritical() << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " "
                        << ptrGrabResult->GetErrorDescription();
        }
    }

    camera_->StopGrabbing();
}

void ImageGrabberThread::startGrabbing(Pylon::CInstantCamera* c) {
    run_flag_ = true;
    camera_ = c;
    start();
}

void ImageGrabberThread::stopGrabbing() {
    run_flag_ = false;
    wait();
}

QImage ImageGrabberThread::grab2image_mono12packed(Pylon::CGrabResultPtr ptrGrabResult) {
    QImage image(ptrGrabResult->GetWidth(), ptrGrabResult->GetHeight(), QImage::Format_Indexed8);
    image.setColorCount(256);
    return image;
}

QImage ImageGrabberThread::grab2image_mono12(Pylon::CGrabResultPtr ptrGrabResult) {
    uint32_t pixel_width = ptrGrabResult->GetWidth();
    uint32_t pixel_height = ptrGrabResult->GetHeight();
    size_t stride_bytes = 0;
    ptrGrabResult->GetStride(stride_bytes);

    QImage image(pixel_width, pixel_height, QImage::Format_Indexed8);
    image.setColorCount(256);

    for (size_t h = 0; h < pixel_height; h++) {
        uint8_t* bufferRow = (uint8_t*)ptrGrabResult->GetBuffer() + h * stride_bytes;
        uint8_t* scanline = (uint8_t*)image.scanLine(h);
        for (size_t w = 0; w < pixel_width; w++) {
            size_t i = w * 2;
            int pixel_value = 0;
            pixel_value |= bufferRow[i + 1];
            pixel_value <<= 8;
            pixel_value += bufferRow[i];
            scanline[w] = pixel_value * 256 / 4096;
        }
    }

    return image;
}

QImage ImageGrabberThread::grab2image_mono8(Pylon::CGrabResultPtr ptrGrabResult) {
    uint32_t pixel_width = ptrGrabResult->GetWidth();
    uint32_t pixel_height = ptrGrabResult->GetHeight();
    size_t stride_bytes = 0;
    ptrGrabResult->GetStride(stride_bytes);

    QImage image(pixel_width, pixel_height, QImage::Format_Indexed8);
    image.setColorCount(256);

    for (size_t h = 0; h < pixel_height; h++) {
        uint8_t* bufferRow = (uint8_t*)ptrGrabResult->GetBuffer() + h * stride_bytes;
        uint8_t* scanline = (uint8_t*)image.scanLine(h);
        for (size_t w = 0; w < pixel_width; w++) {
            uint pixel_value = bufferRow[w];
            scanline[w] = pixel_value;
        }
    }

    return image;
}

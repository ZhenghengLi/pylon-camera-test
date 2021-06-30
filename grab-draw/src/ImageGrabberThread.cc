#include "ImageGrabberThread.hh"
#include <iostream>
#include <QtGlobal>
#include <QDebug>
#include <iostream>

using namespace std;

ImageGrabberThread::ImageGrabberThread() {
    run_flag_ = false;
    camera_ = nullptr;
}

ImageGrabberThread::~ImageGrabberThread() {}

void ImageGrabberThread::run() {
    if (camera_ == nullptr) return;
    try {
        cout << "grabbing ..." << endl;
        doGrabbing_();
        cout << "grabbing finished." << endl;
    } catch (const Pylon::GenericException& e) {
        qCritical() << "Pylon Error: " << e.GetDescription();
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
            std::cout << "SizeX: " << ptrGrabResult->GetWidth() << std::endl;
            std::cout << "SizeY: " << ptrGrabResult->GetHeight() << std::endl;
            std::cout << "PayloadType: " << ptrGrabResult->GetPayloadType() << std::endl;
            std::cout << "PixelType: " << std::hex << ptrGrabResult->GetPixelType() << std::dec << std::endl;
            std::cout << "BufferSize: " << ptrGrabResult->GetBufferSize() << std::endl;

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
#include "ImageGrabber.hh"
#include <iostream>
#include <QDebug>

using namespace std;

ImageGrabber::ImageGrabber() {
    camera_ = nullptr;
    connect(&imageGrabberThread_, &ImageGrabberThread::imageGrabbed, this, &ImageGrabber::imageGrabbed);
}

ImageGrabber::~ImageGrabber() { closeCamera_(); }

void ImageGrabber::openCamera_() {
    if (camera_ != nullptr) return;
    if (imageGrabberThread_.isRunning()) return;

    Pylon::CTlFactory& tlFactory = Pylon::CTlFactory::GetInstance();
    Pylon::DeviceInfoList_t lstDevices;
    tlFactory.EnumerateDevices(lstDevices);
    if (lstDevices.empty()) {
        throw RUNTIME_EXCEPTION("No devices found!");
    }

    camera_ = new Pylon::CInstantCamera(tlFactory.CreateDevice(lstDevices[0]));
    camera_->Open();

    Pylon::CDeviceInfo devinfo = camera_->GetDeviceInfo();
    cout << "camera opened on device: " << devinfo.GetFullName() << endl;

    GenApi::INodeMap& nodemap = camera_->GetNodeMap();

    // Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("Mono12Packed");
    // Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("Mono12");
    Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("Mono8");
}

void ImageGrabber::closeCamera_() {
    if (camera_ == nullptr) return;
    if (imageGrabberThread_.isRunning()) {
        imageGrabberThread_.stopGrabbing();
    }

    camera_->Close();
    delete camera_;
    camera_ = nullptr;
    cout << "camera closed" << endl;
}

void ImageGrabber::open() {
    try {
        openCamera_();
        emit cameraOpened();
    } catch (const Pylon::GenericException& e) {
        qCritical() << "Pylon Error 1: " << e.GetDescription();
    } catch (const std::exception& e) {
        qCritical() << "Error: " << e.what();
    }
}

void ImageGrabber::close() {
    try {
        closeCamera_();
        emit cameraClosed();
    } catch (const Pylon::GenericException& e) {
        qCritical() << "Pylon Error 2: " << e.GetDescription();
    } catch (const std::exception& e) {
        qCritical() << "Error: " << e.what();
    }
}

void ImageGrabber::start() {
    if (camera_ == nullptr) return;
    imageGrabberThread_.startGrabbing(camera_);
}

void ImageGrabber::stop() {
    if (camera_ == nullptr) return;
    imageGrabberThread_.stopGrabbing();
}

#include "ImageGrabber.hh"
#include <iostream>
#include <QDebug>

using namespace std;

ImageGrabber::ImageGrabber() { camera_ = nullptr; }

ImageGrabber::~ImageGrabber() {}

void ImageGrabber::openCamera_() {
    if (camera_ != nullptr) return;

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
    Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("Mono12Packed");
}

void ImageGrabber::closeCamera_() {
    if (camera_ != nullptr) {
        camera_->Close();
        delete camera_;
        camera_ = nullptr;
        cout << "camera closed" << endl;
    }
}

void ImageGrabber::open() {
    try {
        openCamera_();
        emit cameraOpened();
    } catch (const Pylon::GenericException& e) {
        qCritical() << "Pylon Error: " << e.GetDescription();
    } catch (const std::exception& e) {
        qCritical() << "Error: " << e.what();
    }
}

void ImageGrabber::close() {
    try {
        closeCamera_();
        emit cameraClosed();
    } catch (const Pylon::GenericException& e) {
        qCritical() << "Pylon Error: " << e.GetDescription();
    } catch (const std::exception& e) {
        qCritical() << "Error: " << e.what();
    }
}

void ImageGrabber::start() {}

void ImageGrabber::stop() {}

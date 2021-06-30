#include "ImageGrabber.hh"
#include <iostream>

using namespace std;

ImageGrabber::ImageGrabber() {
    //
}

ImageGrabber::~ImageGrabber() {}

void ImageGrabber::openCamera_() {
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
    }
}

void ImageGrabber::open() {}

void ImageGrabber::close() {}

void ImageGrabber::start() {}

void ImageGrabber::stop() {}

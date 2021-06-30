#include "ImageGrabber.hh"
#include <iostream>

using namespace std;

ImageGrabber::ImageGrabber() {
    //
}

ImageGrabber::~ImageGrabber() {}

bool ImageGrabber::openCamera() {
    //
    Pylon::CTlFactory& tlFactory = Pylon::CTlFactory::GetInstance();
    Pylon::DeviceInfoList_t lstDevices;
    tlFactory.EnumerateDevices(lstDevices);
    if (lstDevices.empty()) {
        cerr << "No devices found!" << endl;
        return false;
    }

    camera_ = new Pylon::CInstantCamera(tlFactory.CreateDevice(lstDevices[0]));
    camera_->Open();

    Pylon::CDeviceInfo devinfo = camera_->GetDeviceInfo();
    cout << "camera opened on device: " << devinfo.GetFullName() << endl;

    GenApi::INodeMap& nodemap = camera_->GetNodeMap();
    Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("Mono12Packed");

    return true;
}

void ImageGrabber::closeCamera() {
    if (camera_ != nullptr) {
        camera_->Close();
        delete camera_;
        camera_ = nullptr;
    }
}
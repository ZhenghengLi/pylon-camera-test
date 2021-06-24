#include <ostream>
#include <pylon/PylonIncludes.h>

using namespace Pylon;
using namespace std;

int main() {
    PylonAutoInitTerm autoInitTerm;

    CTlFactory& tlFactory = CTlFactory::GetInstance();
    DeviceInfoList_t lstDevices;
    tlFactory.EnumerateDevices(lstDevices);
    if (lstDevices.empty()) {
        cerr << "No devices found!" << endl;
        return 1;
    }

    CInstantCamera* camera = nullptr;

    try {
        camera = new CInstantCamera(tlFactory.CreateDevice(lstDevices[0]));
    } catch (const GenericException& e) {
        cerr << "Failed to create camera: " << e.GetDescription() << endl;
        return 2;
    }

    CDeviceInfo devinfo = camera->GetDeviceInfo();
    cout << "camera opened on device: " << devinfo.GetFullName() << endl;

    CGrabResultPtr ptrGrabResult;

    camera->StartGrabbing(1000);
    while (camera->IsGrabbing()) {
        camera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);
        //
        if (ptrGrabResult->GrabSucceeded()) {
            // Access the image data.
            cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
            cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
            const uint8_t* pImageBuffer = (uint8_t*)ptrGrabResult->GetBuffer();
            cout << "Gray value of first pixel: " << (uint32_t)pImageBuffer[0] << endl << endl;
        } else {
            cout << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " "
                 << ptrGrabResult->GetErrorDescription() << endl;
        }
    }

    delete camera;
    camera = nullptr;

    return 0;
}
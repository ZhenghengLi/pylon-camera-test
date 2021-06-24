#include <ostream>
#include <fstream>
#include <pylon/PylonIncludes.h>

using namespace Pylon;
using namespace std;

class CPixelFormatAndAoiConfiguration : public Pylon::CConfigurationEventHandler {
public:
    void OnOpened(Pylon::CInstantCamera& camera) {
        try {
            // Allow all the names in the namespace GenApi to be used without qualification.
            using namespace Pylon;
            // Get the camera control object.
            GenApi::INodeMap& nodemap = camera.GetNodeMap();
            // Get the parameters for setting the image area of interest (Image AOI).
            CIntegerParameter width(nodemap, "Width");
            CIntegerParameter height(nodemap, "Height");
            CIntegerParameter offsetX(nodemap, "OffsetX");
            CIntegerParameter offsetY(nodemap, "OffsetY");
            // Maximize the Image AOI.
            offsetX.TrySetToMinimum(); // Set to minimum if writable.
            offsetY.TrySetToMinimum(); // Set to minimum if writable.
            width.SetToMaximum();
            height.SetToMaximum();
            // Set the pixel data format.
            CEnumParameter(nodemap, "PixelFormat").SetValue("Mono12Packed");
            // CEnumParameter(nodemap, "PixelFormat").SetValue("Mono12");
            // CEnumParameter(nodemap, "PixelFormat").SetValue("Mono8");
        } catch (const Pylon::GenericException& e) {
            throw RUNTIME_EXCEPTION(
                "Could not apply configuration. const GenericException caught in OnOpened method msg=%hs", e.what());
        }
    }
};

int process() {

    CTlFactory& tlFactory = CTlFactory::GetInstance();
    DeviceInfoList_t lstDevices;
    tlFactory.EnumerateDevices(lstDevices);
    if (lstDevices.empty()) {
        cerr << "No devices found!" << endl;
        return 2;
    }

    CInstantCamera* camera = new CInstantCamera(tlFactory.CreateDevice(lstDevices[0]));

    CDeviceInfo devinfo = camera->GetDeviceInfo();
    cout << "camera opened on device: " << devinfo.GetFullName() << endl;
    camera->RegisterConfiguration(new CPixelFormatAndAoiConfiguration, RegistrationMode_Append, Cleanup_Delete);

    CGrabResultPtr ptrGrabResult;

    ofstream file("data_Mono12Packed.dat");

    camera->StartGrabbing(1);
    while (camera->IsGrabbing()) {
        camera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);
        //
        if (ptrGrabResult->GrabSucceeded()) {
            // Access the image data.
            cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
            cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
            cout << "PayloadType: " << ptrGrabResult->GetPayloadType() << endl;
            cout << "PixelType: " << hex << ptrGrabResult->GetPixelType() << dec << endl;
            cout << "BufferSize: " << ptrGrabResult->GetBufferSize() << endl;

            file.write((const char*)ptrGrabResult->GetBuffer(), ptrGrabResult->GetBufferSize());

            const uint8_t* pImageBuffer = (uint8_t*)ptrGrabResult->GetBuffer();
            cout << "Gray value of first pixel: " << (uint32_t)pImageBuffer[0] << endl << endl;
        } else {
            cout << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " "
                 << ptrGrabResult->GetErrorDescription() << endl;
        }
    }

    file.close();

    delete camera;
    camera = nullptr;

    return 0;
}

int main() {
    PylonAutoInitTerm autoInitTerm;

    int exitCode = 0;
    try {
        exitCode = process();
    } catch (const GenericException& e) {
        cerr << "Pylon Error: " << e.GetDescription() << endl;
        return -1;
    } catch (const exception& e) {
        cerr << "Error: " << e.what();
        return -2;
    }

    return exitCode;
}
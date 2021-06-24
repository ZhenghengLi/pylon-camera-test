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

    delete camera;
    camera = nullptr;

    return 0;
}
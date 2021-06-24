#include <iostream>
#include <pylon/PylonIncludes.h>

using namespace std;

int main(int argc, char** argv) {

    cout << "before init" << endl;

    Pylon::PylonAutoInitTerm autoInitTerm;

    cout << "after init" << endl;

    return 0;
}

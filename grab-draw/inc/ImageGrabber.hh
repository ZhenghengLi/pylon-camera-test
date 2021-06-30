#ifndef __ImageGrabber_H__
#define __ImageGrabber_H__

#include <pylon/PylonIncludes.h>
#include <QObject>

class ImageGrabber : public QObject {
    Q_OBJECT

public:
    ImageGrabber();
    ~ImageGrabber();

public:
    bool openCamera();
    void closeCamera();

private:
    Pylon::CInstantCamera* camera_ = nullptr;
};

#endif
#ifndef __ImageGrabber_H__
#define __ImageGrabber_H__

#include <pylon/PylonIncludes.h>
#include <QObject>
#include <QImage>

class ImageGrabber : public QObject {
    Q_OBJECT

public:
    ImageGrabber();
    ~ImageGrabber();

public slots:
    void open();
    void close();
    void start();
    void stop();

signals:
    void cameraOpened();
    void cameraClose();
    void grabbingStarted();
    void grabbingStopped();

protected:
    void openCamera_();
    void closeCamera_();

private:
    Pylon::CInstantCamera* camera_ = nullptr;
};

#endif
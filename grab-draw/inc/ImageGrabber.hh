#ifndef __ImageGrabber_H__
#define __ImageGrabber_H__

#include <pylon/PylonIncludes.h>
#include <QObject>
#include <QImage>
#include "ImageGrabberThread.hh"

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
    void cameraClosed();
    void grabbingStarted();
    void grabbingStopped();
    void imageGrabbed(QImage);

protected:
    void openCamera_();
    void closeCamera_();

private:
    Pylon::CInstantCamera* camera_;
    ImageGrabberThread imageGrabberThread_;
};

#endif
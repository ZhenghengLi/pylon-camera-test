#ifndef __ImageGrabberThread_H__
#define __ImageGrabberThread_H__

#include <pylon/PylonIncludes.h>
#include <QThread>
#include <QImage>

class ImageGrabberThread : public QThread {
    Q_OBJECT

public:
    ImageGrabberThread(Pylon::CInstantCamera* c);
    ~ImageGrabberThread();

signals:
    void imageGrabbed(QImage);

protected:
    void run() override;

private:
    Pylon::CInstantCamera* camera_;
};

#endif
#ifndef __ImageGrabberThread_H__
#define __ImageGrabberThread_H__

#include <pylon/PylonIncludes.h>
#include <QThread>
#include <QImage>
#include <atomic>

using std::atomic_bool;

class ImageGrabberThread : public QThread {
    Q_OBJECT

public:
    ImageGrabberThread(Pylon::CInstantCamera* c);
    ~ImageGrabberThread();

signals:
    void imageGrabbed(QImage);

protected:
    void run() override;
    atomic_bool run_flag_;

private:
    void doGrabbing_();

private:
    Pylon::CInstantCamera* camera_;
};

#endif
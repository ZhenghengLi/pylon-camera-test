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
    ImageGrabberThread(QObject* parent = nullptr);
    ~ImageGrabberThread();

public slots:
    void startGrabbing(Pylon::CInstantCamera* c);
    void stopGrabbing();

signals:
    void imageGrabbed(QImage);

protected:
    void run() override;
    atomic_bool run_flag_;

private:
    void doGrabbing_();
    QImage grab2image_mono12packed(Pylon::CGrabResultPtr ptrGrabResult);
    QImage grab2image_mono12(Pylon::CGrabResultPtr ptrGrabResult);
    QImage grab2image_mono8(Pylon::CGrabResultPtr ptrGrabResult);

private:
    Pylon::CInstantCamera* camera_;
};

#endif
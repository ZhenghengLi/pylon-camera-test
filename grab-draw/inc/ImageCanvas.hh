#ifndef __ImageCanvas_H__
#define __ImageCanvas_H__

#include <QWidget>
#include <QImage>

class ImageCanvas : public QWidget {
    Q_OBJECT

public:
    ImageCanvas(QWidget* parent = nullptr);
    ~ImageCanvas();

public slots:
    void drawImage(QImage image);

private:
    QImage currentImage_;
};

#endif
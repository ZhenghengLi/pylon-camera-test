#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QEvent>
#include <QPushButton>

using namespace std;

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    window->setWindowTitle("Enter you age");

    QSpinBox* spinbox = new QSpinBox();
    QSlider* slider = new QSlider(Qt::Horizontal);
    spinbox->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));

    spinbox->setValue(35);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(spinbox);
    layout->addWidget(slider);

    window->setLayout(layout);

    window->show();

    return app.exec();
}

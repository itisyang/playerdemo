#include "CustomSlider.h"
#include "globalhelper.h"

CustomSlider::CustomSlider(QWidget *parent)
    : QSlider(parent)
{
    this->setMaximum(MAX_SLIDER_VALUE);
}

CustomSlider::~CustomSlider()
{
}

void CustomSlider::mousePressEvent(QMouseEvent *ev)
{
    //注意应先调用父类的鼠标点击处理事件，这样可以不影响拖动的情况
    QSlider::mousePressEvent(ev);
    //获取鼠标的位置，这里并不能直接从ev中取值（因为如果是拖动的话，鼠标开始点击的位置没有意义了）
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());

    emit SigCustomSliderValueChanged();
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    QSlider::mouseReleaseEvent(ev);

    //emit SigCustomSliderValueChanged();
}

void CustomSlider::mouseMoveEvent(QMouseEvent *ev)
{
    QSlider::mouseMoveEvent(ev);
    //获取鼠标的位置，这里并不能直接从ev中取值（因为如果是拖动的话，鼠标开始点击的位置没有意义了）
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());

    emit SigCustomSliderValueChanged();
}

#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground, true);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    qDebug() << "press";
    QWidget::mousePressEvent(event);
}

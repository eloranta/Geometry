#include <QMouseEvent>
#include <QPainter>
#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget{parent}{
    setAttribute(Qt::WA_StyledBackground, true);
    updateTransform();
}

void Canvas::resizeEvent(QResizeEvent *event){
    updateTransform();
    QWidget::resizeEvent(event);
}

void Canvas::updateTransform(){
    const int padding = 16;
    QRectF area = rect().adjusted(padding, padding, -padding, -padding);
    const double span = 10.0;
    if (area.width() <= 0.0 || area.height() <= 0.0) {
        scale = 1.0;
        origin = QPointF(0.0, 0.0);
        return;
    }
    scale = std::min(area.width(), area.height()) / span;
    origin = QPointF(area.left() + area.width() / 2.0, area.top() + area.height() / 2.0);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const double radiusPixels = 4.0;
    for (int i = 0; i < points.size(); ++i) {
        const auto &entry = points[i];
        QPointF mapped = CanvasToScreen(entry);
        painter.setBrush(Qt::red);
        painter.setPen(QPen(Qt::red, 2));
        painter.drawEllipse(mapped, radiusPixels, radiusPixels);
        }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    QPointF point = screenToCanvas(event->position());
    qDebug() << point;
    points.append(point);
    update();
    QWidget::mousePressEvent(event);
}

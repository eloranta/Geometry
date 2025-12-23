#include <QMouseEvent>
#include <memory>
#include "canvas.h"

double Canvas::scale;
QPointF Canvas::origin;

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

    for (int i = 0; i < objects.size(); ++i) {
        objects[i]->Paint(painter);
    }
}

int Canvas::getHitPoint(QMouseEvent *event)
{
    int hitPoint = -1;
    double bestDist2 = std::numeric_limits<double>::max();
    const double tolerancePx = 8.0;
    const double tol2 = tolerancePx * tolerancePx;
    for (int i = 0; i < objects.size(); ++i) {
        QPointF screen = canvasToScreen(static_cast<Point *>(objects[i].get())->position); // TODO:
        double dx = screen.x() - event->position().x();
        double dy = screen.y() - event->position().y();
        double d2 = dx * dx + dy * dy;
        if (d2 <= tol2 && d2 < bestDist2) {
            bestDist2 = d2;
            hitPoint = i;
        }
    }

    return hitPoint;
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    bool ctrl = event->modifiers().testFlag(Qt::ControlModifier);
    bool shift = event->modifiers().testFlag(Qt::ShiftModifier);

    int hitPoint = getHitPoint(event);

    if (shift && ctrl) {
        if (hitPoint >= 0)
            return;
        objects.push_back(std::make_unique<Point>(screenToCanvas(event->position()), true));
        update();
    }
    else if (shift){
        if (hitPoint >= 0)
            return;
        for (int i = 0; i < objects.size(); ++i) {
            objects[i]->selected = false;
        }
        objects.push_back(std::make_unique<Point>(screenToCanvas(event->position()), true));
        update();
    }
    else if (ctrl) {
        if (hitPoint >= 0) {
                objects[hitPoint]->selected = true;
            update();
        }
    }
    else {
        if (hitPoint >= 0) {
            for (int i = 0; i < objects.size(); ++i) {
                if (i == hitPoint)
                    objects[i]->selected = !objects[i]->selected;
                else
                    objects[i]->selected = false;
            }
            update();
        }
        else{
            for (int i = 0; i < objects.size(); ++i) {
                objects[i]->selected = false;
            }
            update();
        }
    }

    QWidget::mousePressEvent(event);
}

void Canvas::onDelete(){
    qDebug() << "onDelete";
}

void Canvas::onDeleteAll(){
    qDebug() << "onDeleteAll";

}

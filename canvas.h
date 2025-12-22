#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
protected:
    // void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    double scale;
    QPointF origin;
    void updateTransform();
    QPointF CanvasToScreen(const QPointF &point){
        return QPointF(origin.x() + point.x() * scale, origin.y() - point.y() * scale);
    };
    QPointF screenToCanvas(const QPointF &point){
        return QPointF((point.x() - origin.x()) / scale, -(point.y() - origin.y()) / scale);
    };

signals:
};

#endif // CANVAS_H

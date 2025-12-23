#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    struct Object {
        QString label;
        explicit Object(const QString &label = QString()) : label(label) {}
        virtual ~Object() = default;
    };
    struct Point : public Object {
        QPointF positiom;
        Point() = default;
        Point(const QPointF &point, const QString &label) : Object(label), positiom(point) {}
    };
    struct Line : public Object {
        int a = -1;
        int b = -1;
        Line() = default;
        Line(int a, int b, const QString &label) : Object(label), a(a), b(b) {}
    };
    struct ExtendedLine : public Object {
        QPointF a;
        QPointF b;
        ExtendedLine() = default;
        ExtendedLine(const QPointF &a, const QPointF &b, const QString &label) : Object(label), a(a), b(b) {}
    };
    struct Circle : public Object {
        QPointF center;
        double radius = 0.0;
        Circle() = default;
        Circle(const QPointF &center, double radius, const QString &label = QString()) : Object(label), center(center), radius(radius) {}
    };
public:
    explicit Canvas(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    double scale;
    QPointF origin;
    void updateTransform();

    QVector<QPointF> points;

    QPointF CanvasToScreen(const QPointF &point){
        return QPointF(origin.x() + point.x() * scale, origin.y() - point.y() * scale);
    };
    QPointF screenToCanvas(const QPointF &point){
        return QPointF((point.x() - origin.x()) / scale, -(point.y() - origin.y()) / scale);
    };

signals:
};

#endif // CANVAS_H

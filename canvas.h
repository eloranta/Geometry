#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPointF>
#include <QString>
#include <QVector>
#include <QPainter>

class QPainter;

class Canvas : public QWidget
{
    Q_OBJECT
private:
    struct Object {
        bool select;
        QString label;
        explicit Object(bool select, const QString &label = QString()) : select(select), label(label) {}
        virtual ~Object() = default;
        virtual void Paint(QPainter &) { qDebug() << "Object::Paint"; }
    };
    struct Point : public Object {
        QPointF positiom;
        Point(const QPointF &point, bool select, const QString &label = "") : Object(select, label), positiom(point) {}
        void Paint(QPainter &painter) override {
            qDebug() << "Point::Paint";
            QPointF mapped = CanvasToScreen(positiom);
            painter.setBrush(Qt::red);
            painter.setPen(QPen(Qt::red, 2));
            painter.drawEllipse(mapped, 4, 4);
        }
    };
    struct Line : public Object {
        int a = -1;
        int b = -1;
        Line(int a, int b, bool select, const QString &label) : Object(select, label), a(a), b(b) {}
        void Paint(QPainter &) override { qDebug() << "Line::Paint";}
    };
    struct ExtendedLine : public Object {
        QPointF a;
        QPointF b;
        ExtendedLine(const QPointF &a, const QPointF &b, bool select, const QString &label) : Object(select, label), a(a), b(b) {}
        void Paint(QPainter &) override { qDebug() << "ExtendedLine::Paint";}
    };
    struct Circle : public Object {
        QPointF center;
        double radius = 0.0;
        Circle(const QPointF &center, double radius, bool select, const QString &label = QString()) : Object(select, label), center(center), radius(radius) {}
        void Paint(QPainter &) override {qDebug() << "Circle::Paint";}
    };
public:
    explicit Canvas(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    static double scale;
    static QPointF origin;
    void updateTransform();

    QVector<Object *> points;

    static QPointF CanvasToScreen(const QPointF &point){
        return QPointF(origin.x() + point.x() * scale, origin.y() - point.y() * scale);
    };
    static QPointF screenToCanvas(const QPointF &point){
        return QPointF((point.x() - origin.x()) / scale, -(point.y() - origin.y()) / scale);
    };

signals:
};

#endif // CANVAS_H

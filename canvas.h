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
        bool selected;
        QString label;
        explicit Object(bool selected, const QString &label = QString()) : selected(selected), label(label) {}
        virtual ~Object() = default;
        virtual void Paint(QPainter &) { qDebug() << "Object::Paint"; }
    };
    struct Point : public Object {
        QPointF position;
        Point(const QPointF &point, bool select, const QString &label = "") : Object(select, label), position(point) {}
        void Paint(QPainter &painter) override {
            const double radiusPixels = 4.0;
            QPointF mapped = canvasToScreen(position);
            painter.setBrush(selected ? Qt::yellow : Qt::red);
            painter.setPen(QPen(selected ? Qt::darkYellow : Qt::red, selected ? 3 : 2));
            painter.drawEllipse(mapped, selected ? radiusPixels + 2 : radiusPixels, selected ? radiusPixels + 2 : radiusPixels);
        }
    };
    struct Line : public Object {
        int a = -1;
        int b = -1;
        Line(int a, int b, bool selected, const QString &label) : Object(selected, label), a(a), b(b) {}
        void Paint(QPainter &) override { qDebug() << "Line::Paint";}
    };
    struct ExtendedLine : public Object {
        QPointF a;
        QPointF b;
        ExtendedLine(const QPointF &a, const QPointF &b, bool selected, const QString &label) : Object(selected, label), a(a), b(b) {}
        void Paint(QPainter &) override { qDebug() << "ExtendedLine::Paint";}
    };
    struct Circle : public Object {
        QPointF center;
        double radius = 0.0;
        Circle(const QPointF &center, double radius, bool selected, const QString &label = QString()) : Object(selected, label), center(center), radius(radius) {}
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

    QVector<Object *> objects;

    static QPointF canvasToScreen(const QPointF &point){
        return QPointF(origin.x() + point.x() * scale, origin.y() - point.y() * scale);
    };
    static QPointF screenToCanvas(const QPointF &point){
        return QPointF((point.x() - origin.x()) / scale, -(point.y() - origin.y()) / scale);
    };

    int getHitPoint(QMouseEvent *event);

signals:
};

#endif // CANVAS_H

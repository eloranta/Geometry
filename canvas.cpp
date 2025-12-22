#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground, true);
}

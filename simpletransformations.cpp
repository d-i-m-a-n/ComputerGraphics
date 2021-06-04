#include "simpletransformations.h"

const QPointF rotate(QPointF point, QPointF center, double angle)
{
    point = QPointF(point.x()-center.x(), point.y()-center.y());
    point = QPointF(point.x()*cos(angle) - point.y()*sin(angle),point.x()*sin(angle) + point.y()*cos(angle));
    point = QPointF(point.x()+center.x(), point.y()+center.y());
    return point;
}

QPointF scale(QPointF point, QPointF center, double kX, double kY)
{
    point = QPointF(point.x()-center.x(), point.y()-center.y());

    double tan = point.y() / point.x();
    double angle = -1 * atan(tan);
    point = rotate(point, QPointF(0,0), angle);
    point = QPointF(point.x() * kX, point.y() * kY);
    point = rotate(point, QPointF(0,0), -1 * angle);
    point = QPointF(point.x()+center.x(), point.y()+center.y());
    return point;
}

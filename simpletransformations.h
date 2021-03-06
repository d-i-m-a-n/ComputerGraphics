#ifndef SIMPLETRANSFORMATIONS_H
#define SIMPLETRANSFORMATIONS_H

#include <QPointF>
#include <cmath>


const QPointF rotate(QPointF point, QPointF center, double angle);

QPointF scale(QPointF point, QPointF center, double k);


#endif // SIMPLETRANSFORMATIONS_H

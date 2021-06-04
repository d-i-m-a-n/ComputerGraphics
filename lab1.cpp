#include "lab1.h"

#include <QPainter>
#include <QResizeEvent>
#include <cmath>

#include <simpletransformations.h>

#define PI 3.14159265


Lab1::Lab1(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("Lab 1");
    setFixedSize(1000,600);
    setAutoFillBackground(true);
    setPalette(QPalette(QPalette::Background,Qt::white));

    road[0] = QPointF(this->width()*0.025,this->height()*0.25);
    road[1] = QPointF(this->width()*0.975,this->height()*0.975);

    center = QPointF(road[0].x() + 30, road[0].y() - 40);
    markedPoint = QPointF(center.x() + 10, center.y() - 20);
    octangle[0] = QPointF(road[0]);
    for(int i = 1; i < 8; i++)
        octangle[i] = rotate(octangle[i-1],center, 45.0 * PI / 180);
}

void Lab1::resizeEvent(QResizeEvent *event)
{

    QSize newSize = event->size();
    QSize oldSize = event->oldSize();

    if(oldSize.width() < 0)
        return;

    double kX = (double)newSize.width() / (double)oldSize.width();
    double kY = (double)newSize.height() / (double)oldSize.height();

    road[0] = scale(road[0], QPointF(0,0), kX, kY);
    road[1] = scale(road[1], QPointF(0,0), kX, kY);

    center = scale(center, QPointF(0,0), kX, kY);

    for(int i = 0; i < 8; i++)
            octangle[i] = scale(octangle[i], center, kX, kY);

//    center = QPoint(road[0].x() + 30, road[0].y() - 40);

//    octangle[0] = QPointF(road[0]);
//    for(int i = 1; i < 8; i++)
//        octangle[i] = turn(octangle[i-1],center,45);


}

void Lab1::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen;
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawLine(road[0],road[1]);

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);

    painter.setPen(pen);
    painter.drawPoint(center);


    painter.drawLine(octangle[0],octangle[7]);
    for(int i = 1; i < 8; i++)
        painter.drawLine(octangle[i],octangle[i-1]);

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(markedPoint);
}

void Lab1::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == myTimer)
    {

        center = QPointF(center.x() + 5, center.y() + 1.5);
        markedPoint = QPointF(markedPoint.x() + 5, markedPoint.y() + 1.5);
        markedPoint = rotate(markedPoint, center, 5.0 * PI / 180);

        bool reachedRightSide = false;
        for(int i = 0; i < 8; i++)
        {
            octangle[i] = QPointF(octangle[i].x() + 5, octangle[i].y() + 1.5);
            octangle[i] = rotate(octangle[i],center, 5.0 * PI / 180);
            octangle[i] = scale(octangle[i],center, 1.01, 1.01);
            if (octangle[i].x() > this->width())
                reachedRightSide = true;
        }

        if(reachedRightSide)
        {
            center = QPoint(road[0].x() + 30, road[0].y() - 40);
            markedPoint = QPointF(center.x() + 10, center.y() - 20);
            octangle[0] = QPointF(road[0]);
            for(int i = 1; i < 8; i++)
                octangle[i] = rotate(octangle[i-1],center, 45.0 * PI / 180);
        }

        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Lab1::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    myTimer = startTimer(100);
}

void Lab1::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(myTimer);
}


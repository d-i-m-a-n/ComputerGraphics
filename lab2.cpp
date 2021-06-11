#include "lab2.h"
#include <cmath>
#include <QPainter>
#include <QTimerEvent>

#define PI 3.14159265

Lab2::Lab2(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Lab 2");
    setFixedSize(1000,600);
    setAutoFillBackground(true);
    setPalette(QPalette(QPalette::Background,Qt::white));

    computeCoordinates();
}

void Lab2::computeCoordinates()
{

    Matrix T = {{1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {-obsCoord[0],-obsCoord[1],-obsCoord[2],1}};
    Matrix S = {{-1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {0,0,0,1}};
    Matrix Rx90 = {{1,0,0,0},
                   {0,0,-1,0},
                   {0,1,0,0},
                   {0,0,0,1}};

    double d = std::sqrt(std::pow(obsCoord[0],2) + std::pow(obsCoord[1],2));
    double sinU;
    double cosU;
    if (d == 0)
    {
        sinU = 0;
        cosU = 1;
    } else {
        sinU = obsCoord[0] / d;
        cosU = obsCoord[1] / d;
    }

    Matrix Ry = {{cosU,0,sinU,0},
                 {0,1,0,0},
                 {-sinU,0,cosU,0},
                 {0,0,0,1}};

    double s = std::sqrt(std::pow(obsCoord[0],2) + std::pow(obsCoord[1],2) + std::pow(obsCoord[2],2));
    double sinW;
    double cosW;
    if(s == 0)
    {
        sinW = 0;
        cosW = 1;
    } else {
        sinW = obsCoord[2] / s;
        cosW = d / s;
    }

    Matrix Rx = {{1,0,0,0},
                 {0,cosW,-sinW,0},
                 {0,sinW,cosW,0},
                 {0,0,0,1}};


    Matrix V = T*S*Rx90*Ry*Rx;

    Matrix VerNa(NV,3);

    for(int i = 0; i < NV; i++)
    {
        Matrix buf = {{Ver[i][0],Ver[i][1],Ver[i][2],1}};
        VerNa[i] = (buf * V)[0];
    }

    Matrix VerKa(NV,2);

    for(int i = 0; i < NV; i++)
    {
        if (VerNa[i][2] != 0)
        {
            VerKa[i][0] = VerNa[i][0] / VerNa[i][2] * s;
            VerKa[i][1] = VerNa[i][1] / VerNa[i][2] * s;
        }
        else
            VerNa[i][0] = VerNa[i][1] = -1;
    }


    double Pk = 3;
    double Xc = 500;
    double Yc = 300;
    double Xe = 300;
    double Ye = 200;

    for(int i = 0 ; i < NV; i++)
    {
        VerEk[i][0] = (VerKa[i][0] * Xe / Pk) + Xc;
        VerEk[i][1] = (VerKa[i][1] * Ye / Pk + Yc) * (-1) + 2*Yc;
    }

}

void Lab2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    for(auto reb : Reb)
    {
        painter.drawLine(VerEk[reb[0]][0],VerEk[reb[0]][1],VerEk[reb[1]][0],VerEk[reb[1]][1]);
    }
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);

    painter.setPen(pen);
    painter.drawPoint(VerEk[markedNode][0],VerEk[markedNode][1]);
    painter.drawLine(VerEk[Reb[markedReb][0]][0],VerEk[Reb[markedReb][0]][1],VerEk[Reb[markedReb][1]][0],VerEk[Reb[markedReb][1]][1]);

}

void Lab2::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    myTimer = startTimer(50);
}

void Lab2::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == myTimer)
    {
        double x = obsCoord[0];
        double angle = 2 * PI /180;
        obsCoord[0] = x * cos(angle) - obsCoord[1] * sin(angle);
        obsCoord[1] = x * sin(angle) + obsCoord[1] * cos(angle);
//        obsCoord[0] -= 2;
//        obsCoord[2] += 4;
        computeCoordinates();
        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Lab2::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(myTimer);
}

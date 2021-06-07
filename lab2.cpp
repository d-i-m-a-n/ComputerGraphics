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

    double T[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {-obsCoord[0],-obsCoord[1],-obsCoord[2],1}};
    double S [4][4] = {{-1,0,0,0},
                       {0,1,0,0},
                       {0,0,1,0},
                       {0,0,0,1}};
    double Rx90 [4][4] = {{1,0,0,0},
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

    double Ry[4][4] = {{cosU,0,sinU,0},
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

    double Rx[4][4] = {{1,0,0,0},
                       {0,cosW,-sinW,0},
                       {0,sinW,cosW,0},
                       {0,0,0,1}};


    double **V = productOfMatrix(T,S,Rx90,Ry,Rx);

    double VerNa[NV][3];

    for(int i = 0; i < NV; i++)
    {
        double buf[4] = {Ver[i][0],Ver[i][1],Ver[i][2],1};
        for(int j = 0; j < 3; j++)
        {
            VerNa[i][j] = buf[1]*V[1][j] + buf[2]*V[2][j] + buf[3]*V[3][j] + buf[0]*V[0][j];
        }
    }

    double VerKa[NV][2];

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
        VerEk[i][1] = (VerKa[i][1] * Ye / Pk + Yc) * (-1) + 500;
    }


    for(int i = 0; i < 4; i++)
        delete[] V[i];
    delete[] V;
}

double** Lab2::productOfMatrix(double matrix1[4][4],double matrix2[4][4],double matrix3[4][4],double matrix4[4][4],double matrix5[4][4])
{
    double **buf = new double*[4];
    for(int i = 0; i < 4;i++)
    {
        buf[i] = new double[4];
        for(int j = 0; j < 4; j++)
            buf[i][j] = matrix1[i][1]*matrix2[1][j] + matrix1[i][2]*matrix2[2][j] + matrix1[i][3]*matrix2[3][j] + matrix1[i][0]*matrix2[0][j];
    }

    double **buf2 = new double*[4];
    for(int i = 0; i < 4;i++)
    {
        buf2[i] = new double[4];
        for(int j = 0; j < 4; j++)
            buf2[i][j] = buf[i][1]*matrix3[1][j] + buf[i][2]*matrix3[2][j] + buf[i][3]*matrix3[3][j] + buf[i][0]*matrix3[0][j];
    }

    for(int i = 0; i < 4;i++)
    {
        for(int j = 0; j < 4; j++)
            buf[i][j] = buf2[i][1]*matrix4[1][j] + buf2[i][2]*matrix4[2][j] + buf2[i][3]*matrix4[3][j] + buf2[i][0]*matrix4[0][j];
    }

    for(int i = 0; i < 4;i++)
    {
        for(int j = 0; j < 4; j++)
            buf2[i][j] = buf[i][1]*matrix5[1][j] + buf[i][2]*matrix5[2][j] + buf[i][3]*matrix5[3][j] + buf[i][0]*matrix5[0][j];
    }

    for(int i = 0; i < 4; i++)
        delete[] buf[i];
    delete[] buf;

    return buf2;
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
    myTimer = startTimer(5000);
}

void Lab2::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == myTimer)
    {
        obsCoord[0] -= 2;
        obsCoord[2] += 4;
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

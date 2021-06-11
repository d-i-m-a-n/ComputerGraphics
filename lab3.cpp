#include "lab3.h"
#include <cmath>
#include <QTimerEvent>
#include <QPainter>

#define PI 3.14159265


Lab3::Lab3(QWidget *parent) : QWidget(parent), bodyMatrix(4,NGr)
{
    this->setWindowTitle("Lab 3");
    setFixedSize(1000,600);
    setAutoFillBackground(true);
    setPalette(QPalette(QPalette::Background,Qt::white));

    computeCoordinates();
    computeBodyMatrix();
    checkGran();
}

void Lab3::computeCoordinates()
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


void Lab3::checkGran()
{

    NGrVid = 0;
    for(int i = 0; i < NGr; i++)
    {
        if(bodyMatrix[0][i]*obsCoord[0] + bodyMatrix[1][i]*obsCoord[1] + bodyMatrix[2][i]*obsCoord[2] + bodyMatrix[3][i] < 0)
        {
            GranVid[NGrVid] = i;
            NGrVid ++;
        }
    }

}

void Lab3::computeBodyMatrix()
{
    for(int i = 0; i < 3; i++)
    {
        bodyCentre[i] = 0;
        for(int j = 0; j < NV; j++)
            bodyCentre[i] += Ver[j][i];
        bodyCentre[i] /= (double)NV;
    }


    int i = 0;
    for(auto &facet : gran)
    {
        double A = (Ver[facet[2]][1] - Ver[facet[0]][1])*(Ver[facet[1]][2] - Ver[facet[0]][2]) -
                (Ver[facet[1]][1] - Ver[facet[0]][1])*(Ver[facet[2]][2] - Ver[facet[0]][2]);
        double B = (Ver[facet[1]][0] - Ver[facet[0]][0])*(Ver[facet[2]][2] - Ver[facet[0]][2]) -
                (Ver[facet[2]][0] - Ver[facet[0]][0])*(Ver[facet[1]][2] - Ver[facet[0]][2]);
        double C = (Ver[facet[2]][0] - Ver[facet[0]][0])*(Ver[facet[1]][1] - Ver[facet[0]][1]) -
                (Ver[facet[1]][0] - Ver[facet[0]][0])*(Ver[facet[2]][1] - Ver[facet[0]][1]);
        double D = -(A*Ver[facet[0]][0] + B*Ver[facet[0]][1] + C*Ver[facet[0]][2]);

        if (A*bodyCentre[0] + B*bodyCentre[1] + C*bodyCentre[2] + D < 0)
        {
            A *= -1;
            B *= -1;
            C *= -1;
            D *= -1;
        }

        bodyMatrix[0][i] = A;
        bodyMatrix[1][i] = B;
        bodyMatrix[2][i] = C;
        bodyMatrix[3][i] = D;
        i++;
    }
}

void Lab3::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    for(int i = 0; i < NGrVid; i++)
    {
        int curGr = GranVid[i];
        int curVer1 = gran[curGr][0];
        int curVer2 = gran[curGr][1];
        int k = 2;
        while (curVer2 >= 0)
        {
            painter.drawLine(VerEk[curVer1][0],VerEk[curVer1][1],VerEk[curVer2][0],VerEk[curVer2][1]);\
            curVer1 = curVer2;
            curVer2 = gran[curGr][k];
            k++;
        }

    }


}

void Lab3::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    myTimer = startTimer(50);
}

void Lab3::timerEvent(QTimerEvent *event)
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
        computeBodyMatrix();
        checkGran();
        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Lab3::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(myTimer);
}

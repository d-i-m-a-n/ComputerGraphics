#include "lab4.h"
#include <QPainter>
#include <QPoint>
#include <cmath>
#include <QTimerEvent>

#include <algorithm>

#define PI 3.14159265

Lab4::Lab4(QWidget *parent) :QWidget(parent),
    ver(stepCount*stepCount,4), rotation(4,4), corners_
{
    { xMin, 0, zMin, 1 },
    { xMax, 0, zMin, 1 },
    { xMin, 0, zMax, 1 },
    { xMax, 0, zMax, 1 },
}
{
    this->setWindowTitle("Lab 4");
    setFixedSize(600,400);
    setAutoFillBackground(true);
    setPalette(QPalette(QPalette::Background,Qt::black));


    float stepZ = (zMax - zMin) / stepCount;
    float stepX = (xMax - xMin) / stepCount;
    int k = 0;
    float z = zMin;
    for(int i = 0; i < stepCount; i++, z += stepZ)
    {
        float x = xMin;
        for(int j = 0; j < stepCount; j++, x += stepX, k++)
        {
            ver[k][0] = x;
            ver[k][1] = y(x,z);
            ver[k][2] = z;
            ver[k][3] = 1;
        }
    }

    setAngles(angleX,angleY);
}

void Lab4::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QVector<int> horizonUp(this->width());
    QVector<int> horizonDown(this->width());

    horizonUp.fill(0);
    horizonDown.fill(this->height());

    Matrix vertices = scale(ver * rotation) *
            Matrix{{1,0,0,0},
                   {0,-1,0,0},
                   {0,0,0,0},
                   {300,200,0,1}};

    int x0, y0, x1, y1;
    bool visibilityPrev;
    bool visibilityCur;

    for(int i = 0, curPos = 0; i < stepCount; i++)
    {
        for(int j = 0; j < stepCount; j++, curPos++)
        {
            x1 = std::round(vertices[curPos][0]);
            y1 = std::round(vertices[curPos][1]);

            visibilityCur = y1 > horizonUp[x1] || y1 < horizonDown[x1];

            if(j && (visibilityCur || visibilityPrev))
            {
                int dx = std::abs(x1 - x0);
                int dy = std::abs(y1 - y0);
                int ix = -1;
                if (x0 < x1)
                    ix = 1;
                int iy = -1;
                if(y0 < y1)
                    iy = 1;

                int e = 2*dy - dx;
                for(int i = 0; i < dx; i++)
                {
                    if(y0 > horizonUp[x0])
                    {
                        horizonUp[x0] = y0;
                        painter.setPen(Qt::red);
                        painter.drawPoint(x0,y0);
                    }
                    if (y0 < horizonDown[x0])
                    {
                        horizonDown[x0] = y0;
                        painter.setPen(Qt::blue);
                        painter.drawPoint(x0,y0);
                    }

                    if(e >= 0)
                    {
                        y0 += iy;
                        e -= 2*dx;
                    }
                    e += 2*dy;
                    x0 += ix;
                }

            } else
            {
                x0 = x1;
                y0 = y1;
                visibilityPrev = visibilityCur;
            }
        }
    }
}

const Matrix Lab4::scale(const Matrix &vertices)
{
    Matrix corners = corners_ * rotation;

    float norm_x = abs((*std::max_element(corners.begin(), corners.end(), [](const row &a, const row &b) { return abs(a[0]) < abs(b[0]); }))[0]);
    float norm_y = abs((*std::max_element(vertices.begin(), vertices.end(), [](const row &a, const row &b) { return abs(a[1]) < abs(b[1]); }))[1]);

    float k = std::min(this->width() / 2 / norm_x, this->height() / 2 / norm_y) - 1.0f;

    return vertices * Matrix
        {
            { k, 0, 0, 0 },
            { 0, k, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 1 },
        };
}

void Lab4::setAngles(float rotationX, float rotationY)
{
    float sinX = std::sin(rotationX * PI / 180);
    float cosX = std::cos(rotationX * PI / 180);
    float sinY = std::sin(rotationY * PI / 180);
    float cosY = std::cos(rotationY * PI / 180);
    rotation = Matrix({{cosY,0,sinY,0},
                       {0,1,0,0},
                       {-sinY,0,cosY,0},
                       {0,0,0,1}}) *
               Matrix({{1,0,0,0},
                       {0,cosX,-sinX,0},
                       {0,sinX,cosX,0},
                       {0,0,0,1}});
}

float Lab4::y(const float &x, const float &z)
{
    //1
    //return std::abs(x) + std::abs(z);
    //3
    //return  x*x-z*z;
    //7
    return (std::exp(-std::sqrt(x*x + z*z)) - 0.5);
}


void Lab4::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    myTimer = startTimer(1000);
}

void Lab4::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == myTimer)
    {
        if(angleY > 45 || angleY < -45)
            dA *= -1;
        angleY += dA;
        setAngles(angleX,angleY);
        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Lab4::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(myTimer);
}

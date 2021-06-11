#include "lab4.h"
#include <QPainter>
#include <QPoint>
#include <cmath>

#define PI 3.14159265

Lab4::Lab4(QWidget *parent) :QWidget(parent),
    ver(stepCount*stepCount,4), rotation(4,4)
{
    this->setWindowTitle("Lab 4");
    setFixedSize(1000,600);
    setAutoFillBackground(true);
    setPalette(QPalette(QPalette::Background,Qt::white));


    double stepZ = (zMax - zMin) / stepCount;
    double stepX = (xMax - xMin) / stepCount;
    int i = 0;
    for(double z = zMin; z < zMax; z += stepZ)
    {
        for(double x = xMin; x < xMax; x += stepX)
        {
            double Y = y(x,z);
            ver[i][0] = x;
            ver[i][1] = Y;
            ver[i][2] = z;
            ver[i][3] = 1;
        }
    }

    setAngles(0,0);
}

void Lab4::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QVector<double> horizonUp(this->width());
    QVector<double> horizonDown(this->width());

    horizonUp.fill(0);
    horizonDown.fill(this->height());

    Matrix vertices = ver * rotation * Matrix({{100,0,0,0},
    {0,100,0,0},
    {0,0,0,0},
    {0,0,0,1}}) * Matrix({{1,0,0,0},
                                               {0,-1,0,0},
                                               {0,0,0,0},
                                               {300,500,0,1}});


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

                int e = 2*dy - dx;
                for(int i = 0; i < dx; i++)
                {
                    if(y0 > horizonUp[x0])
                    {
                        horizonUp[x0] = y0;
                        painter.drawPoint(x0,y0);
                    }
                    if (y0 < horizonDown[x0])
                    {
                        horizonDown[x0] = y0;
                        painter.drawPoint(x0,y0);
                    }

                    if(e >= 0)
                    {
                        y0++;
                        e -= 2*dx;
                    }
                    e += 2*dy;
                    x0++;
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

void Lab4::scale(Matrix &vertices)
{

}

void Lab4::setAngles(double rotationX, double rotationY)
{
    double sinX = std::sin(rotationX * PI / 180);
    double cosX = std::cos(rotationX * PI / 180);
    double sinY = std::sin(rotationY * PI / 180);
    double cosY = std::cos(rotationY * PI / 180);
    rotation = Matrix({{cosY,0,sinY,0},
                       {0,1,0,0},
                       {-sinY,0,cosY,0},
                       {0,0,0,1}}) *
               Matrix({{1,0,0,0},
                       {0,cosX,-sinX,0},
                       {0,sinX,cosX,0},
                       {0,0,0,1}});
}

double Lab4::y(const double &x, const double &z)
{
    return (std::exp(-std::sqrt(x*x + z*z)) - 0.5);
}

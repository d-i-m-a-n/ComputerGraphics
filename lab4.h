#ifndef LAB4_H
#define LAB4_H

#include <QWidget>

#include "matrix.h"

class Lab4 : public QWidget
{
    Q_OBJECT
public:
    Lab4(QWidget *parent = nullptr);


private:
    // y = exp(-sqrt(x*x+z*z)) - 0.5 :: -2 <= x <= 2 , -2 <= z <= 2

    void paintEvent(QPaintEvent *event) override;
    void scale(Matrix &vertices);
    void setAngles(double rotationX, double rotationY);
    double y(const double &x, const double &z);


    double xMin = -2;
    double xMax = 2;
    double zMin = -2;
    double zMax = 2;
    int stepCount = 100;
    Matrix ver;
    Matrix rotation;
};

#endif // LAB4_H

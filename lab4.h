#ifndef LAB4_H
#define LAB4_H

#include <QWidget>

#include "matrix.h"

#define PI 3.14159265

class Lab4 : public QWidget
{
    Q_OBJECT
public:
    Lab4(QWidget *parent = nullptr);


private:
    // y = exp(-sqrt(x*x+z*z)) - 0.5 :: -2 <= x <= 2 , -2 <= z <= 2

    void paintEvent(QPaintEvent *event) override;
    const Matrix scale(const Matrix &vertices);
    void setAngles(float rotationX, float rotationY);
    float y(const float &x, const float &z);
    //1
//    float xMin = -5;
//    float xMax = 5;
//    float zMin = -1;
//    float zMax = 1;
    //3 + 7
    float xMin = -2;
    float xMax = 2;
    float zMin = -2;
    float zMax = 2;
    int stepCount = 100;
    Matrix ver;
    Matrix rotation;
    Matrix corners_;
    float angleY = 0;
    float angleX = 10;
    float dA = 5;
    int myTimer;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // LAB4_H

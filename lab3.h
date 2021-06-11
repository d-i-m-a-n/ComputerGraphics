#ifndef LAB3_H
#define LAB3_H

#include <QWidget>

#include "matrix.h"

class Lab3 : public QWidget
{
    Q_OBJECT
public:
    Lab3(QWidget *parent = nullptr);

private:

    void computeCoordinates();
    void computeBodyMatrix();
    void checkGran();

//    int NV = 5;
//    int NGr = 5;
//    int NGrVid = 0;
//    Matrix Ver = {{1,-2,2},
//                  {-1,-3,2},
//                  {-1,3,2},
//                  {1,2,2},
//                  {0,0,7}};
//    int gran[5][5] = {{1,2,3,4,1},
//                   {1,2,5,1,0},
//                   {2,3,5,2,0},
//                   {3,4,5,3,0},
//                   {1,4,5,1,0}};


    const int NV = 6;
    const int NR = 9;
    int NGr = 5;
    int NGrVid = 0;
    Matrix Ver = {{0,2,1.5},
                  {0,-2,1.5},
                  {0,2,-1.5},
                  {0,-2,-1.5},
                  {2,0,1.5},
                  {2,0,-1.5}};
    int Reb[9][2] = {{0,1},{0,2},{0,4},{1,3},{1,4},{2,3},{2,5},{3,5},{4,5}};

    int gran[5][6] = {{0,1,4,0,-1,-1},
                      {2,3,5,2,-1,-1},
                      {0,1,3,2,0,-1},
                      {0,2,5,4,0,-1},
                      {1,3,5,4,1,-1}};

    int markedNode = 0;
    int markedReb = 8;
    double obsCoord[3] = {10,0,5};
    double VerEk[9][2];

    Matrix bodyMatrix;
    int GranVid[5];
    double bodyCentre[3];

    int myTimer;
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

};

#endif // LAB3_H

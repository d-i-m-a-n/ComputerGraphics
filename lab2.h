#ifndef LAB2_H
#define LAB2_H

#include <QWidget>

class Lab2 : public QWidget
{
    Q_OBJECT

public:
    Lab2(QWidget *parent = nullptr);


private:
    void paintEvent(QPaintEvent *event) override;

    void computeCoordinates();
    double** productOfMatrix(double matrix1[4][4], double matrix2[4][4], double matrix3[4][4], double matrix4[4][4], double matrix5[4][4]);

    double Ver[6][3] = {{0,2,1.5},
                        {0,-2,1.5},
                        {0,2,-1.5},
                        {0,-2,-1.5},
                        {2,0,1.5},
                        {2,0,-1.5}};
    int Reb[9][2] = {{0,1},{0,2},{0,4},{1,3},{1,4},{2,3},{2,5},{3,5},{4,5}};
    int markedNode = 0;
    int markedReb = 8;
    double obsCoord[3] = {10,0,0};
    double VerEk[9][2];
    const int NV = 6;
    const int NR = 9;


    int myTimer;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // LAB2_H

#ifndef LAB1_H
#define LAB1_H

#include <QWidget>

class Lab1 : public QWidget
{
    Q_OBJECT

public:
    Lab1(QWidget *parent = nullptr);

private:

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

    int myTimer;

    QPointF octangle[8];
    QPointF center;
    QPointF markedPoint;
    QPointF road[2];
};

#endif // LAB1_H

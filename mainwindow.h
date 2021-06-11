#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Lab1 lab1;
    Lab2 lab2;
    Lab3 lab3;
    Lab4 lab4;
};
#endif // MAINWINDOW_H

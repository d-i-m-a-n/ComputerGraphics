#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    lab1 = new Lab1(this);
//    lab2 = new Lab2(this);

    connect(ui->pushButton_lab1,SIGNAL(clicked()),&lab1,SLOT(show()));
    connect(ui->pushButton_lab2,SIGNAL(clicked()),&lab2,SLOT(show()));
    connect(ui->pushButton_lab2,SIGNAL(clicked()),&lab3,SLOT(show()));
    connect(ui->pushButton_lab4,SIGNAL(clicked()),&lab4,SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


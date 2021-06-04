#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_lab1,SIGNAL(clicked()),&lab1,SLOT(show()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


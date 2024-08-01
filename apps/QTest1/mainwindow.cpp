#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../libs/utils/utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Utils utils;
    int val = utils.calcSum((int)3, (int)4);
    int val2 = calcSum2((int)1, (int)2);
    QString str = QString("Utils calc sum = %1, sum2=%2").arg(QString::number(val), QString::number(val2));
    ui->label->setText(str);
}


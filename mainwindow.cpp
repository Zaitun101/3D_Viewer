#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(num_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::num_pressed()
{
    qDebug() << ui->doubleSpinBox->text();
    scale = ui->doubleSpinBox->text().toDouble();
}

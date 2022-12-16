#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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


void MainWindow::on_scale_valueChanged(double arg1)
{
    this->ui->GLwidget->scale = arg1;
}


void MainWindow::on_line_valueChanged(double arg1)
{
    this->ui->GLwidget->line_width = arg1;
}


void MainWindow::on_dots_valueChanged(double arg1)
{
    this->ui->GLwidget->dots_width = arg1;
}


void MainWindow::on_file_released()
{
    QString file_path;
    file_path = QFileDialog::getOpenFileName(this, tr("Выберите файл"), "//", tr("Object (*.obj)"));
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    this->ui->GLwidget->line = checked;
}


void MainWindow::on_xPos_valueChanged(double arg1)
{
    this->ui->GLwidget->xPos = arg1;
}


void MainWindow::on_yPos_valueChanged(double arg1)
{
    this->ui->GLwidget->yPos = arg1;
}


void MainWindow::on_zPos_valueChanged(double arg1)
{
    this->ui->GLwidget->zPos = arg1;
}


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
    ui->GLwidget->updateGL();
}


void MainWindow::on_line_valueChanged(double arg1)
{
    this->ui->GLwidget->line_width = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_dots_valueChanged(double arg1)
{
    this->ui->GLwidget->dots_width = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_file_released()
{
    QString file_path;
    file_path = QFileDialog::getOpenFileName(0, "Выберите файл", "//", ("*.obj"));
    QStringList tmp = file_path.split('/');
    if (tmp.size()!= 1) {
        this->ui->label_5->setText(tmp[tmp.size() - 1]);
    }
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    this->ui->GLwidget->line = checked;
    ui->GLwidget->updateGL();
}


void MainWindow::on_xPos_valueChanged(double arg1)
{
    this->ui->GLwidget->xPos = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_yPos_valueChanged(double arg1)
{
    this->ui->GLwidget->yPos = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_zPos_valueChanged(double arg1)
{
    this->ui->GLwidget->zPos = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_bg_color_clicked()
{
    this->ui->GLwidget->bg_color = QColorDialog::getColor(Qt::black, this);
    ui->GLwidget->updateGL();
}


void MainWindow::on_ribs_color_clicked()
{
    this->ui->GLwidget->ribs_color = QColorDialog::getColor(Qt::white, this);
    ui->GLwidget->updateGL();
}


void MainWindow::on_pushButton_clicked()
{
    this->ui->GLwidget->dots_color = QColorDialog::getColor(Qt::green, this);
    ui->GLwidget->updateGL();
}



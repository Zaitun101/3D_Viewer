#include "mainwindow.h"

#include <QDebug>

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_scale_valueChanged(double arg1) {
  scale(&ui->GLwidget->obj, arg1, this->ui->GLwidget->scale);
  ui->GLwidget->updateGL();
  this->ui->GLwidget->scale = arg1;
}

void MainWindow::on_line_valueChanged(double arg1) {
  this->ui->GLwidget->line_width = arg1;
  ui->GLwidget->updateGL();
}

void MainWindow::on_dots_valueChanged(double arg1) {
  this->ui->GLwidget->dots_width = arg1;
  ui->GLwidget->updateGL();
}

void MainWindow::on_file_released() {
  QString file_path;
  file_path = QFileDialog::getOpenFileName(0, "Выберите файл", "//", ("*.obj"));
//  file_path = "../../../workdir/lamp.obj";
  QStringList tmp = file_path.split('/');
  if (tmp.size() != 1) {
    this->ui->GLwidget->filepath = file_path;
    this->ui->GLwidget->free_mem();
    this->ui->label_5->setText(tmp[tmp.size() - 1]);
    this->ui->label_7->setText(
        "Количество вершин: " +
        QString::number(ui->GLwidget->obj.count_vert / 3) +
        "\nКоличество ребер: " +
        QString::number(ui->GLwidget->obj.count_facets / 6));
    this->ui->GLwidget->updateGL();
  }
}

void MainWindow::on_checkBox_clicked(bool checked) {
  this->ui->GLwidget->line = checked;
  ui->GLwidget->updateGL();
}

void MainWindow::on_xPos_valueChanged(double arg1) {
  move_obj(&ui->GLwidget->obj, arg1, ui->GLwidget->xPos, 0, 0, 0, 0);
  ui->GLwidget->updateGL();
  this->ui->GLwidget->xPos = arg1;
}

void MainWindow::on_yPos_valueChanged(double arg1) {
  move_obj(&ui->GLwidget->obj, 0, 0, arg1, ui->GLwidget->yPos, 0, 0);
  ui->GLwidget->updateGL();
  this->ui->GLwidget->yPos = arg1;
}

void MainWindow::on_zPos_valueChanged(double arg1) {
  move_obj(&ui->GLwidget->obj, 0, 0, 0, 0, arg1, ui->GLwidget->zPos);
  ui->GLwidget->updateGL();
  this->ui->GLwidget->zPos = arg1;
}

void MainWindow::on_bg_color_clicked() {
  this->ui->GLwidget->bg_color = QColorDialog::getColor(Qt::black, this);
  ui->GLwidget->updateGL();
}

void MainWindow::on_ribs_color_clicked() {
  this->ui->GLwidget->ribs_color = QColorDialog::getColor(Qt::white, this);
  ui->GLwidget->updateGL();
}

void MainWindow::on_pushButton_clicked() {
  this->ui->GLwidget->dots_color = QColorDialog::getColor(Qt::green, this);
  ui->GLwidget->updateGL();
}

void MainWindow::on_x_rot_valueChanged(double arg1) {
  ui->GLwidget->updateGL();
  this->ui->GLwidget->xRot = arg1;
}

void MainWindow::on_x_rot_button_released() {
  rot_x(&ui->GLwidget->obj, this->ui->GLwidget->xRot);
  ui->GLwidget->updateGL();
}

void MainWindow::on_y_rot_valueChanged(double arg1) {
  ui->GLwidget->updateGL();
  this->ui->GLwidget->yRot = arg1;
}

void MainWindow::on_y_rot_button_released() {
  rot_y(&ui->GLwidget->obj, this->ui->GLwidget->yRot);
  ui->GLwidget->updateGL();
}

void MainWindow::on_z_rot_valueChanged(double arg1) {
  ui->GLwidget->updateGL();
  this->ui->GLwidget->zRot = arg1;
}

void MainWindow::on_pushButton_2_released() {
  rot_z(&ui->GLwidget->obj, this->ui->GLwidget->zRot);
  ui->GLwidget->updateGL();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  ui->GLwidget->dot_type = index;
  ui->GLwidget->updateGL();
}

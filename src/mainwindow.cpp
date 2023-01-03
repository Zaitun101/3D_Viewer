#include "mainwindow.h"


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
  QColor bg_color = QColorDialog::getColor(Qt::black, this);
  ui->GLwidget->bg_red = bg_color.redF();
  ui->GLwidget->bg_green = bg_color.greenF();
  ui->GLwidget->bg_blue = bg_color.blueF();
  ui->GLwidget->updateGL();
}

void MainWindow::on_ribs_color_clicked() {
  QColor line_color = QColorDialog::getColor(Qt::white, this);
  ui->GLwidget->line_red = line_color.redF();
  ui->GLwidget->line_green = line_color.greenF();
  ui->GLwidget->line_blue = line_color.blueF();
  ui->GLwidget->updateGL();
}

void MainWindow::on_pushButton_clicked() {
  QColor dots_color = QColorDialog::getColor(Qt::green, this);
  ui->GLwidget->dots_red = dots_color.redF();
  ui->GLwidget->dots_green = dots_color.greenF();
  ui->GLwidget->dots_blue = dots_color.blueF();
  ui->GLwidget->updateGL();
}

void MainWindow::on_x_rot_valueChanged(double arg1) {
  this->ui->GLwidget->xRot = arg1;
  ui->GLwidget->updateGL();
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

void MainWindow::on_comboBox_2_currentIndexChanged(int index) {
  ui->GLwidget->proj = index;
  ui->GLwidget->projection();
  ui->GLwidget->updateGL();
}

void MainWindow::on_save_exit_clicked() {
  ui->GLwidget->save_settings();
//  exit(1);
}

void MainWindow::on_load_settings_released()
{
    ui->GLwidget->load_settings();
    ui->line->setValue(ui->GLwidget->line_width);
    ui->dots->setValue(ui->GLwidget->dots_width);
    ui->comboBox->setCurrentIndex(ui->GLwidget->dot_type);
    ui->checkBox->setChecked(ui->GLwidget->line);
    ui->comboBox_2->setCurrentIndex(ui->GLwidget->proj);
    QString file_path = ui->GLwidget->filepath;
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
    }
    ui->GLwidget->updateGL();
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    ui->GLwidget->tr1 = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    ui->GLwidget->tr2 = arg1;
    ui->GLwidget->updateGL();
}


void MainWindow::on_save_jpeg_released()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "../saved/name.jpeg");
    ui->GLwidget->grabFrameBuffer().save(file, NULL, 100);
}


void MainWindow::on_save_bmp_released()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "../saved/name.bmp");
    ui->GLwidget->grabFrameBuffer().save(file, NULL, 100);
}


void MainWindow::on_start_record_released()
{
    gif = 1;
    if (gif == 1) {
            mas_image.push_back(ui->GLwidget->grab().toImage());
        }
}


void MainWindow::on_save_record_released()
{
    gif = 0;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save screenshot"), "", tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
    QGifImage gif(QSize(5000, 5000));
    QVector<QRgb> ctable;
    ctable << qRgb(255, 255, 255)
           << qRgb(0, 0, 0)
           << qRgb(255, 0, 0)
           << qRgb(0, 255, 0)
           << qRgb(0, 0, 255)
           << qRgb(255, 255, 0)
           << qRgb(0, 255, 255)
           << qRgb(255, 0, 255);

    gif.setGlobalColorTable(ctable, Qt::black);
    gif.setDefaultTransparentColor(Qt::black);
    gif.setDefaultDelay(100);

    for (QVector<QImage>::Iterator img = mas_image.begin(); img != mas_image.end(); ++img) {
        gif.addFrame(*img);
    }
    gif.save(fileName);

}




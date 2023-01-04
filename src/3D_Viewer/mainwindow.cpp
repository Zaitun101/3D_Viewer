#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3DViewer");
  this->setFixedSize(this->size());
  time = 0.0;
  record_time = new QTimer(this);
  connect(record_time, &QTimer::timeout, this, &MainWindow::recording);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_scale_valueChanged(double arg1) {
  if (ui->GLwidget->obj.count_facets > 3)
    change_scale(&ui->GLwidget->obj, arg1, this->ui->GLwidget->scale);
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
  file_path =
      QFileDialog::getOpenFileName(0, "Выберите файл", "../obj", ("*.obj"));
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
  if (ui->GLwidget->obj.count_facets > 3)
    move_obj(&ui->GLwidget->obj, arg1, ui->GLwidget->xPos, 0, 0, 0, 0);
  ui->GLwidget->updateGL();
  this->ui->GLwidget->xPos = arg1;
}

void MainWindow::on_yPos_valueChanged(double arg1) {
  if (ui->GLwidget->obj.count_facets > 3)
    move_obj(&ui->GLwidget->obj, 0, 0, arg1, ui->GLwidget->yPos, 0, 0);
  ui->GLwidget->updateGL();
  this->ui->GLwidget->yPos = arg1;
}

void MainWindow::on_zPos_valueChanged(double arg1) {
  if (ui->GLwidget->obj.count_facets > 3)
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
  if (ui->GLwidget->obj.count_facets > 3)
    rot_x(&ui->GLwidget->obj, this->ui->GLwidget->xRot);
  ui->GLwidget->updateGL();
}

void MainWindow::on_y_rot_valueChanged(double arg1) {
  ui->GLwidget->updateGL();
  this->ui->GLwidget->yRot = arg1;
}

void MainWindow::on_y_rot_button_released() {
  if (ui->GLwidget->obj.count_facets > 3)
    rot_y(&ui->GLwidget->obj, this->ui->GLwidget->yRot);
  ui->GLwidget->updateGL();
}

void MainWindow::on_z_rot_valueChanged(double arg1) {
  ui->GLwidget->updateGL();
  this->ui->GLwidget->zRot = arg1;
}

void MainWindow::on_pushButton_2_released() {
  if (ui->GLwidget->obj.count_facets > 3)
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

void MainWindow::on_save_exit_clicked() { ui->GLwidget->save_settings(); }

void MainWindow::on_load_settings_released() {
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

void MainWindow::on_save_jpeg_released() {
  QString file = QFileDialog::getSaveFileName(
      this, tr("Save as..."), "../saved/name.jpeg", tr("JPEG (*.jpeg)"));
  ui->GLwidget->grabFrameBuffer().save(file, NULL, 100);
}

void MainWindow::on_save_bmp_released() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "../saved/name.bmp", tr("BMP (*.bmp)"));
  ui->GLwidget->grabFrameBuffer().save(file, NULL, 100);
}

void MainWindow::on_start_record_released() {
  if (is_recording == 0) {
    is_recording = 1;
    record_time->start(100);
  }
}

void MainWindow::recording() {
  if (is_recording && time <= 5.0) {
    gif.push_back(ui->GLwidget->grabFrameBuffer());
    time += 0.1;
    if (int(time) % 2 == 1) {
      ui->label_10->setText("");
    } else {
      ui->label_10->setStyleSheet("QLabel { color : red; }");
      ui->label_10->setText("Идет запись!");
    }
  } else {
    on_save_record_released();
    record_time->stop();
  }
}

void MainWindow::on_save_record_released() {
  QString str = QFileDialog::getSaveFileName(this, tr("Save GIF"), "../saved",
                                             tr("GIF (*.gif)"));
  if (str != "") {
    QGifImage giF(QSize(712, 801));

    giF.setDefaultTransparentColor(Qt::red);
    giF.setDefaultDelay(100);

    for (QVector<QImage>::Iterator frame = gif.begin(); frame != gif.end();
         frame++) {
      giF.addFrame(*frame);
    }

    giF.save(str);
    gif.clear();
  }
  time = 0.0;
  is_recording = 0;
  ui->label_10->setText("");
}

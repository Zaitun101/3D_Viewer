#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../GIFCreation/gifImage/qgifimage.h"
#include <QDebug>
#include "glwidget.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int is_recording = 0;
  QTimer *record_time;
  QVector<QImage> gif;
  float time;
 private slots:
  void on_scale_valueChanged(double arg1);

  void on_line_valueChanged(double arg1);

  void on_dots_valueChanged(double arg1);

  void on_checkBox_clicked(bool checked);

  void on_xPos_valueChanged(double arg1);

  void on_yPos_valueChanged(double arg1);

  void on_zPos_valueChanged(double arg1);

  void on_bg_color_clicked();

  void on_ribs_color_clicked();

  void on_pushButton_clicked();

  void on_file_released();

  void on_x_rot_valueChanged(double arg1);

  void on_x_rot_button_released();

  void on_y_rot_valueChanged(double arg1);

  void on_y_rot_button_released();

  void on_pushButton_2_released();

  void on_z_rot_valueChanged(double arg1);

  void on_comboBox_currentIndexChanged(int index);

  void on_comboBox_2_currentIndexChanged(int index);

  void on_save_exit_clicked();

  void on_load_settings_released();

  void on_save_jpeg_released();

  void on_start_record_released();

  void on_save_record_released();

  void on_save_bmp_released();

  void recording();

private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

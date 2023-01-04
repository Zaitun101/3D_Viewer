#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QColorDialog>
#include <QGLWidget>
#include <QSettings>
#include <QWidget>
#include <QtOpenGL/QtOpenGL>

extern "C" {
#include <../parser.h>
}

class GLWidget : public QGLWidget {
  Q_OBJECT
private:
  QSettings *settings;
  QPoint mPos;
  void draw();
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

public:
  GLWidget(QWidget *parent = 0);
  void free_mem();
  void projection();
  void save_settings();
  void load_settings();
  float xRot = 0.25, yRot = 0.25, zRot = 0.25;
  array_data obj = {0, 0, 0, 0, 0};
  double scale = 1;
  double line_width = 1;
  double dots_width = 2;
  double xPos, yPos, zPos;
  int line = 0;
  QString filepath;
  int dot_type = 0;
  int proj = 0;
  float line_red = 0;
  float line_green = 1;
  float line_blue = 0;
  float dots_red = 1;
  float dots_green = 0;
  float dots_blue = 0;
  float bg_red = 0;
  float bg_green = 0;
  float bg_blue = 0;
  char *res_str = 0;

  double start_x;
  double start_y;
};

#endif // GLWIDGET_H

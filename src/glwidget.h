#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QColorDialog>
#include <QGLWidget>
#include <QTimer>
#include <QWidget>
#include <QtOpenGL/QtOpenGL>
extern "C" {
#include <../parser.h>
}

class GLWidget : public QGLWidget {
  Q_OBJECT
 private:
  QPoint mPos;
  QTimer timer;
  void drawCube();
  void projection();
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 public:
  float xRot = 0.0, yRot = 0.0, zRot = 0.0;
  float xRot1 = 0, yRot1 = 0;
  GLWidget(QWidget *parent = 0);
  array_data obj = {0, 0, 0, 0, 0};
  double scale;
  double line_width;
  double dots_width;
  double xPos, yPos, zPos, ang;
  int line;
  QColor ribs_color = Qt::green;
  QColor bg_color;
  QColor dots_color = Qt::red;
  QString filepath = "../heart.obj";
  void free_mem();
  int dot_type = 0;
};

#endif  // GLWIDGET_H

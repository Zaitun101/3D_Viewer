#include "glwidget.h"

#include <QDebug>

#include "mainwindow.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
  settings = new QSettings("../settings.conf", QSettings::IniFormat);
}

void GLWidget::free_mem() {
  std::setlocale(LC_NUMERIC, "POSIX");
  if (obj.facets != NULL && obj.vertexes != NULL) {
    free(obj.facets);
    free(obj.vertexes);
    obj.facets = 0;
    obj.vertexes = 0;
    obj.count_facets = 0;
    obj.count_vert = 0;
  }
  QByteArray str_bit = filepath.toLocal8Bit();
  res_str = str_bit.data();
  if (res_str != NULL) {
    allocate_memory(&obj, res_str);
    array(&obj, res_str);
    index1(&obj, res_str);
  }
}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (proj == 0) {
    glOrtho(-1, 1, -1, 1, -15, 15);
  } else {
    glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 5);
  }
}

void GLWidget::paintGL() {
  projection();
  glClearColor(bg_red, bg_green, bg_blue, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -1.8);
  draw();
}

void GLWidget::mousePressEvent(QMouseEvent *mo) {
  mPos = mo->pos();
  start_x = mo->pos().x();
  start_y = mo->pos().y();
}

void GLWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - start_y) / 60;
  yRot = 1 / M_PI * (mo->pos().x() - start_x) / 60;
  rot_x(&obj, xRot);
  rot_y(&obj, yRot);
  start_x = mo->pos().x();
  start_y = mo->pos().y();
  updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *wheel) {
  double prev_scale = scale;
  if ((wheel->delta()) > 0)
    scale *= 1.05;
  else if ((wheel->delta()) < 0)
    scale /= 1.05;
  if (obj.count_facets > 3)
    change_scale(&obj, scale, prev_scale);
  updateGL();
}

void GLWidget::draw() {
  int count = obj.count_facets;
  int line_value = 0xFFFF;
  if (line)
    line_value = 0xFF01;
  glLineStipple(1, line_value);
  glEnable(GL_LINE_STIPPLE);
  glVertexPointer(3, GL_DOUBLE, 0, obj.vertexes);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (dot_type == 1)
    glEnable(GL_POINT_SMOOTH);
  glPointSize(dots_width);
  glColor3d(dots_red, dots_green, dots_blue);
  if (dot_type != 0)
    glDrawElements(GL_POINTS, count, GL_UNSIGNED_INT, obj.facets);
  glLineWidth(line_width);
  glColor3d(line_red, line_green, line_blue);
  glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, obj.facets);
  glDisableClientState(GL_VERTEX_ARRAY);
  if (dot_type == 1)
    glDisable(GL_POINT_SMOOTH);
  glDisable(GL_LINE_STIPPLE);
}

void GLWidget::save_settings() {
  settings->setValue("line_red", line_red);
  settings->setValue("line_green", line_green);
  settings->setValue("line_blue", line_blue);
  settings->setValue("dots_red", dots_red);
  settings->setValue("dots_green", dots_green);
  settings->setValue("dots_blue", dots_blue);
  settings->setValue("bg_red", bg_red);
  settings->setValue("bg_green", bg_green);
  settings->setValue("bg_blue", bg_blue);
  settings->setValue("line_type", line);
  settings->setValue("dots_type", dot_type);
  settings->setValue("line_width", line_width);
  settings->setValue("dots_width", dots_width);
  settings->setValue("proj", proj);
  settings->setValue("file_path", filepath);
}

void GLWidget::load_settings() {
  line_red = settings->value("line_red", line_red).toFloat();
  line_green = settings->value("line_green", line_green).toFloat();
  line_blue = settings->value("line_blue", line_blue).toFloat();
  dots_red = settings->value("dots_red", dots_red).toFloat();
  dots_green = settings->value("dots_green", dots_green).toFloat();
  dots_blue = settings->value("dots_blue", dots_blue).toFloat();
  bg_red = settings->value("bg_red", bg_red).toFloat();
  bg_green = settings->value("bg_green", bg_green).toFloat();
  bg_blue = settings->value("bg_blue", bg_blue).toFloat();
  line = settings->value("line_type", line).toInt();
  dot_type = dot_type = settings->value("dots_type", dot_type).toInt();
  line_width = settings->value("line_width", line_width).toInt();
  dots_width = settings->value("dots_width", dots_width).toInt();
  proj = settings->value("proj", proj).toInt();
  filepath = settings->value("file_path", filepath).toString();
}

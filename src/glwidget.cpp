#include "glwidget.h"
#include "mainwindow.h"
#include <QDebug>


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    this->scale = 1.0;
    this->line_width = 1.0;
    this->dots_width = 2.0;
    this->zPos = -2.0;
    this->line = false;
    timer.start(16);
}



void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}


   void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 1.5, 100);
    glOrtho(-12, 12, -12, 12, -12, 12);
}


void GLWidget::paintGL() {
    glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(),0);
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(scale, scale, 1);
    glTranslatef(xPos, yPos, zPos);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(ang, 1, 1, 1);
    drawCube();
}


void GLWidget::mousePressEvent(QMouseEvent * mo) {
    mPos = mo->pos();
    xRot1 = xRot;
    yRot1 = yRot;
}


void GLWidget::mouseMoveEvent(QMouseEvent * mo) {
    xRot = xRot1 + 1/M_PI*(mo->pos().y() - mPos.y());
    yRot = yRot1 + 1/M_PI*(mo->pos().x() - mPos.x());
    updateGL();
}



void GLWidget::drawCube() {


    float ver_cub[] = {
        0 ,0, 2,
        0 , 0 , -2,
        0, 8, 0,
        3, 3, 0,
        9, 2, 0,
        5, -3, 0,
        6, -9, 0,
        0, -7, 0,
        -6, -9, 0,
        -5, -3, 0,
        -9, 2, 0,
        -3, 3, 0,
    };

    int index_cub[] = {
        0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 0, 10, 1, 10, 0, 11, 1, 11, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10, 10, 11, 11, 2
    };



    int count = 60;
    int line_value = 0xFFFF;
    if (line)
        line_value = 0xFF01;
    glLineStipple(1, line_value);
    glEnable(GL_LINE_STIPPLE);
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(dots_width);
    glColor3d(dots_color.redF(), dots_color.greenF(), dots_color.blueF());
    glDrawElements(GL_POINTS, count, GL_UNSIGNED_INT, index_cub);
    glLineWidth(line_width);
    glColor3d(ribs_color.redF(), ribs_color.greenF(), ribs_color.blueF());
    glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, index_cub);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
}


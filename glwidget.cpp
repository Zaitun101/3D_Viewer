#include "glwidget.h"
#include "mainwindow.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}


void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}


void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 0.5, 7);
}


void GLWidget::paintGL() {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawCube(0.5);
}


void GLWidget::mousePressEvent(QMouseEvent * mo) {
    mPos = mo->pos();
}


void GLWidget::mouseMoveEvent(QMouseEvent * mo) {
    xRot=1/M_PI*(mo->pos().y() - mPos.y());
    yRot=1/M_PI*(mo->pos().x() - mPos.x());
    updateGL();
}


void GLWidget::drawCube(float a) {
    float ver_cub[] = {

        1.000000 ,-1.000000, -1.000000,
        1.000000 ,-1.000000, 1.000000,
       -1.000000, -1.000000, 1.000000,
       -1.000000, -1.000000, -1.000000,
        1.000000 ,1.000000 ,-0.999999,
        0.999999 ,1.000000 ,1.000001,
       -1.000000, 1.000000, 1.000000,
        -1.000000, 1.000000, -1.000000
    };

    int index_cub[] = {
        0,1,2,3,7,6,5,4,7,0,5,1,6,2,7,3,0,4,7,4,  1, 2,5,6,7,3,0,3
    };

    float color_arr[] = {
        1,0,0,  1,0,0,  1,0,0,  1,0,0,    // front
        0,0,1,  0,0,1,  0,0,1,  0,0,1,    // back
        1,1,0,  1,1,0,  1,1,0,  1,1,0,    // left
        0,1,1,  0,1,1,  0,1,1,  0,1,1,    // right
        1,0,1,  1,0,1,  1,0,1,  1,0,1,    // down
        1,1,1,  1,1,1,  1,1,1,  1,1,1     // down
    };

    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
        glDrawElements(GL_POINTS, 28, GL_UNSIGNED_INT, index_cub);
        glDrawElements(GL_LINES, 28, GL_UNSIGNED_INT, index_cub);
    glDisableClientState(GL_VERTEX_ARRAY);
}


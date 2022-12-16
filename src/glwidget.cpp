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
    connect(  &timer,  SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(16);
}


void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    }


    void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 1, 10);
    glOrtho(-12, 12, -12, 12, -12, 12);
}


void GLWidget::paintGL() {

//    ang += 0.5;
    glClearColor(0,0,0,0);
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
}


void GLWidget::mouseMoveEvent(QMouseEvent * mo) {
    xRot=1/M_PI*(mo->pos().y() - mPos.y());
    yRot=1/M_PI*(mo->pos().x() - mPos.x());
    updateGL();
}



void GLWidget::drawCube() {
//    float ver_cub[] = {
//        7.889562 ,1.150329 ,-2.173651,
//        2.212808 ,1.150329 ,-3.230414,
//        0.068023 ,1.150328 ,-7.923502,
//        -2.151306 ,1.150329 ,-2.254857,
//        -7.817406 ,1.150328 ,-2.261558,
//        -3.523133, 1.150328, 1.888122,
//        -4.869315, 1.150328, 6.987552,
//        -0.006854, 1.150329, 4.473047,
//        4.838127, 1.150328, 7.041885,
//        3.538153, 1.150329, 1.927652,
//        0.033757 ,0.000000 ,-0.314657,
//        0.035668 ,2.269531 ,-0.312831,
//    };

//    int index_cub[] = {
//        10, 11
//    };

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




//    float color_arr[] = {
//        1, 1, 1, 0    // front
////        0,0,1,  0,0,1,  0,0,1,  0,0,1,    // back
////        1,1,0,  1,1,0,  1,1,0,  1,1,0,    // left
////        0,1,1,  0,1,1,  0,1,1,  0,1,1,    // right
////        1,0,1,  1,0,1,  1,0,1,  1,0,1,    // down
////        1,1,1,  1,1,1,  1,1,1,  1,1,1     // down
//    };
    int count = 60;
    int line_value = 0xFFFF;
    if (line)
        line_value = 0xFF01;
    glLineStipple(1, line_value);
    glEnable(GL_LINE_STIPPLE);
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(line_width);
    glPointSize(dots_width);
//    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glColor3d(1, 1, 0);
//    glEnableClientState(GL_COLOR_ARRAY);
        glDrawElements(GL_POINTS, count, GL_UNSIGNED_INT, index_cub);
//    glDrawArrays(GL_POINTS, 0, 8);
        glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, index_cub);
    glDisableClientState(GL_VERTEX_ARRAY);
}


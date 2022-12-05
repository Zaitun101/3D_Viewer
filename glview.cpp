#include "glview.h"
#include "ui_glview.h"

glview::glview(QWidget *parent)
    : QGLWidget(parent)
{
    setWindowTitle("Viewer");
    setGeometry(300, 200, 800, 600);
}



void glview::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}


void glview::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 5);
}



void glview::paintGL() {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawCube(0.5);
}

void glview::mousePressEvent(QMouseEvent * mo) {
    mPos = mo->pos();
}

void glview::mouseMoveEvent(QMouseEvent * mo) {
    xRot=1/M_PI*(mo->pos().y() - mPos.y());
    yRot=1/M_PI*(mo->pos().x() - mPos.x());
    updateGL();
}

void glview::drawCube(float a) {
    float ver_cub[] = {
        -a, -a, a,      a, -a, a,       a, a, a,     -a, a, a,
        a, -a, -a,      -a, -a, -a,     -a, a, -a,  a, a, -a,
        -a, -a, -a,     -a, -a, a,      -a, a, a,    -a, a, -a,
        a, -a, a,       a, -a, -a,      a, a, -a,    a, a, a,
        -a, -a, a,      a, -a, a,       a, -a, -a,   -a, -a, -a,
        -a, a, a,       a, a, a,        a, a, -a,    -a, a, -a,
    };

    float color_arr[] = {
        1,0,1,  1,0,1,  1,0,0,  1,0,0,
        0,0,1,  0,0,1,  0,0,1,  0,0,1,
        1,1,0,  1,1,0,  1,1,0,  1,1,0,
        0,1,1,  0,1,1,  0,1,1,  0,1,1,
        1,0,1,  1,0,1,  0,0,1,  0,0,1,
        1,0.5, 0.5, 1, 0.5, 0.5, 1, 0.5,0.5, 1, 0.5,0.5
    };

    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);

}



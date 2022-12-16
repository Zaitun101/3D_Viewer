#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QTimer>



class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer timer;

    void drawCube();
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*)override;
    void initializeGL()override;
    void resizeGL(int w, int h)override;
    void paintGL()override;


public:
    GLWidget(QWidget *parent = 0);
    double scale;
    double line_width;
    double dots_width;
    double xPos, yPos, zPos, ang;
    int line;
};






#endif // GLWIDGET_H

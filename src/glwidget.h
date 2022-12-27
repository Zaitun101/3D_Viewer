#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QTimer>
#include <QColorDialog>


class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    float xRot = 0.0, yRot = 0.0, zRot;
    float xRot1 = 0, yRot1 = 0;
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
    QColor ribs_color = Qt::green;
    QColor bg_color;
    QColor dots_color = Qt::red;
    QString filepath;
    void free_mem();
};






#endif // GLWIDGET_H

#ifndef GLVIEW_H
#define GLVIEW_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class glview; }
QT_END_NAMESPACE

class glview : public QGLWidget
{
    Q_OBJECT
private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(float a);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*)override;
    void initializeGL()override;
    void resizeGL(int w, int h)override;
    void paintGL()override;

public:
    glview(QWidget *parent = nullptr);


private:
    Ui::glview *ui;
};
#endif // GLVIEW_H

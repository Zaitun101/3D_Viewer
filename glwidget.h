#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>


namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double scale;

private slots:

    void on_pushButton_2_released();

    void on_doubleSpinBox_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};




class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    double line_width;
    void set_line(double x){
        line_width = x;
    }
    void drawCube();
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*)override;
    void initializeGL()override;
    void resizeGL(int w, int h)override;
    void paintGL()override;


public:
    GLWidget(QWidget *parent = 0);
};






#endif // GLWIDGET_H

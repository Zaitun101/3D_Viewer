#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_scale_valueChanged(double arg1);

    void on_line_valueChanged(double arg1);

    void on_dots_valueChanged(double arg1);

    void on_file_released();

    void on_checkBox_clicked(bool checked);

    void on_xPos_valueChanged(double arg1);

    void on_yPos_valueChanged(double arg1);

    void on_zPos_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

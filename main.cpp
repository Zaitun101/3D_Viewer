#include "glview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glview w;
    w.show();
    return a.exec();
}

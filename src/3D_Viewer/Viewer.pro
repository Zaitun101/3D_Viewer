QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../GIFCreation/gifImage/qgifimage.cpp \
    ../../GIFCreation/gifLib/dgif_lib.c \
    ../../GIFCreation/gifLib/egif_lib.c \
    ../../GIFCreation/gifLib/gif_err.c \
    ../../GIFCreation/gifLib/gif_font.c \
    ../../GIFCreation/gifLib/gif_hash.c \
    ../../GIFCreation/gifLib/gifalloc.c \
    ../../GIFCreation/gifLib/quantize.c \
    ../parser.c \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    glwidget.h \
    mainwindow.h \
    ../parser.h \
    ../../GIFCreation/gifImage/qgifglobal.h \
    ../../GIFCreation/gifImage/qgifimage.h \
    ../../GIFCreation/gifImage/qgifimage_p.h \
    ../../GIFCreation/gifLib/gif_hash.h \
    ../../GIFCreation/gifLib/gif_lib.h \
    ../../GIFCreation/gifLib/gif_lib_private.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    ../../GIFCreation/CMakeLists.txt \
    ../../GIFCreation/CMakeLists.txt.user

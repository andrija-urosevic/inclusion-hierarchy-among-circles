QT       += core gui opengl charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lglut -lGLU

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithm.cpp \
    animationthread.cpp \
    canvas.cpp \
    canvasopengl.cpp \
    circle.cpp \
    main.cpp \
    mainwindow.cpp \
    myalgorithm.cpp \
    timemeasurementthread.cpp

HEADERS += \
    algorithm.h \
    animationthread.h \
    canvas.h \
    canvasopengl.h \
    circle.h \
    mainwindow.h \
    myalgorithm.h \
    timemeasurementthread.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    InclusionHierarchyAmongCircles_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

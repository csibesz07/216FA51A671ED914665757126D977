#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T22:06:05
#
#-------------------------------------------------

QT       += core gui

TARGET = CAGD_PROJECT
TEMPLATE = app


SOURCES += main.cpp\
    Core/TriangulatedMeshes3.cpp \
    Core/TensorProductSurfaces3.cpp \
    Core/ShaderPrograms.cpp \
    Core/RealSquareMatrices.cpp \
    Core/Materials.cpp \
    Core/LinearCombination3.cpp \
    Core/Lights.cpp \
    Core/GenericCurves3.cpp \
    Core/BicubicBezierPatches.cpp \
    GUI/SideWidget.cpp \
    GUI/MainWindow.cpp \
    GUI/GLWidget.cpp \

HEADERS  += Core/TriangulatedMeshes3.h \
    Core/TriangularFaces.h \
    Core/TensorProductSurfaces3.h \
    Core/TCoordinates4.h \
    Core/ShaderPrograms.h \
    Core/RealSquareMatrices.h \
    Core/Matrices.h \
    Core/Materials.h \
    Core/LinearCombination3.h \
    Core/Lights.h \
    Core/HCoordinates3.h \
    Core/GenericCurves3.h \
    Core/Exceptions.h \
    Core/DCoordinates3.h \
    Core/Constants.h \
    Core/Colors4.h \
    Core/BicubicBezierPatches.h \
    GUI/SideWidget.h \
    GUI/MainWindow.h \
    GUI/GLWidget.h

OTHER_FILES += \
    Core/mouse.off \
    Core/elephant.off

QT += opengl

INCLUDEPATH += ./Dependencies/Include
LIBS += ./Dependencies/Lib/GL/glew32.dll ./Dependencies/Lib/GL/glew32.lib

FORMS += \
    GUI/SideWidget.ui \
    GUI/MainWindow.ui

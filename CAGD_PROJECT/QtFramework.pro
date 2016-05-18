SOURCES += \
    main.cpp \
    GUI/MainWindow.cpp \
    GUI/GLWidget.cpp \
    GUI/SideWidget.cpp \
    Core/RealSquareMatrices.cpp \
    Core/TriangulatedMeshes3.cpp \
    Core/Materials.cpp \
    Core/ShaderPrograms.cpp \
    Core/LinearCombination3.cpp \
    Core/GenericCurves3.cpp \
    Core/TensorProductSurfaces3.cpp \
    Core/Lights.cpp \
    Core/BicubicBezierPatches.cpp

HEADERS += \
    GUI/MainWindow.h \
    GUI/GLWidget.h \
    GUI/SideWidget.h \
    Core/RealSquareMatrices.h \
    Core/Matrices.h \
    Core/DCoordinates3.h \
    Core/TriangulatedMeshes3.h \
    Core/TriangularFaces.h \
    Core/TCoordinates4.h \
    Core/Materials.h \
    Core/HCoordinates3.h \
    Core/Exceptions.h \
    Core/Colors4.h \
    Core/Constants.h \
    Core/ShaderPrograms.h \
    Core/LinearCombination3.h \
    Core/GenericCurves3.h \
    Core/TensorProductSurfaces3.h \
    Core/Lights.h \
    Core/BicubicBezierPatches.h

FORMS += \
    GUI/MainWindow.ui \
    GUI/SideWidget.ui \

QT += opengl

INCLUDEPATH += ./Dependencies/Include
LIBS += ./Dependencies/Lib/GL/glew32.dll ./Dependencies/Lib/GL/glew32.lib

OTHER_FILES += \
    Core/mouse.off \
    Core/elephant.off

CONFIG += console

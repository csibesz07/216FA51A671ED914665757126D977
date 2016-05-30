#pragma once

// GLU was removed from Qt starting from version 4.8

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include <QTimer>
#include "../Core/TriangulatedMeshes3.h"
#include "../Core/ShaderPrograms.h"
#include "../Core/BicubicBezierPatches.h"

class GLWidget: public QGLWidget
{
    Q_OBJECT
protected:
    //model
    cagd::ShaderProgram _shader;

private:
    QTimer* _timer;
    GLfloat _angle;

    // variables defining the projection matrix
    float       _aspect;            // aspect ratio of the rendering window
    float       _fovy;              // field of view in direction y
    float       _z_near, _z_far;    // distance of near and far clipping planes

    // variables defining the model-view matrix
    float       _eye[3], _center[3], _up[3];

    // variables needed by transformations
    int         _angle_x, _angle_y, _angle_z;
    double      _zoom;
    double      _trans_x, _trans_y, _trans_z;

    cagd::TriangulatedMesh3 _model;

    cagd::TriangulatedMesh3 _mouse;

    bool _apply_shader;

    cagd::BicubicBezierPatch     _patch;
    cagd::TriangulatedMesh3      *_before_interpolation, *_after_interpolation, *_mesh;
    cagd::CompositeBezierSurface *cs;

public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

    // redeclared virtual functions
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *event);

    ~GLWidget();

public slots:
    // public event handling methods/slots
    void _animate();
    void set_angle_x(int value);
    void set_angle_y(int value);
    void set_angle_z(int value);

    void set_zoom_factor(double value);

    void set_trans_x(double value);
    void set_trans_y(double value);
    void set_trans_z(double value);

    void setShaderStatus(bool value);




    //void select_x_point(int value);
    void select_y_point(QString value);
    void set_point_x_position(int value);
   /* void set_point_y_position(int value);
    void set_point_z_position(int value);
    void select_patch_for_join();
    void set_first_joning_side(QString value);
    void set_second_joning_side(QString value);*/
};

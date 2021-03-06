#include "GLWidget.h"
#include "../Core/Materials.h"
#include "../Core/Constants.h"
#include "../Core/Exceptions.h"
using namespace cagd;
using namespace std;
//--------------------------------
// special and default constructor
//--------------------------------
GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
{
    _timer = new QTimer(this);
    _timer->setInterval(0);

    connect( _timer , SIGNAL(timeout()) , this , SLOT(_animate()) ) ;
}

//--------------------------------------------------------------------------------------
// this virtual function is called once before the first call to paintGL() or resizeGL()
//--------------------------------------------------------------------------------------
void GLWidget::initializeGL()
{
    glewInit();

    // creating a perspective projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)width() / (float)height();
    _z_near = 1.0;
    _z_far = 1000.0;
    _fovy = 45.0;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // setting the model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
    _center[0] = _center[1] = _center[2] = 0.0;
    _up[0] = _up[2] = 0.0, _up[1] = 1.0;

    gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

    // enabling depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // initial values of transformation parameters
    _zoom = 1.0;
    _angle_x = _angle_y = _angle_z = 0.0;
    _trans_x = _trans_y = _trans_z = 0.0;


    /*
    if (_mouse.LoadFromOFF("Models/mouse.off" , true ))
        if ( _mouse.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW))
        {
            _angle = 0.0;
            _timer->start();
        }

    // creating a perspective projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)width() / (float)height();
    _z_near = 1.0;
    _z_far = 1000.0;
    _fovy = 45.0;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // setting the model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
    _center[0] = _center[1] = _center[2] = 0.0;
    _up[0] = _up[2] = 0.0, _up[1] = 1.0;

    gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

    // enabling depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    if (_model.LoadFromOFF("Models/mouse.off", true))
    {
        _model.UpdateVertexBufferObjects();
    }

    // setting the color of background
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // initial values of transformation parameters
    _zoom = 1.0;
    _angle_x = _angle_y = _angle_z = 0.0;
    _trans_x = _trans_y = _trans_z = 0.0;

    //model
    try
    {
//       _shader.InstallShaders("Shaders/toon.vert","Shaders/toon.frag",true);
       _shader.InstallShaders("Shaders/directional_light.vert","Shaders/directional_light.frag",true);
       _shader.Enable();
//       _shader.SetUniformVariable4f("default_outline_color", 1.0, 0.0, 0.0, 1.0);
       //piros,zold,kek,fekete
//       _shader.SetUniformVariable4f("mycolor", 0.5, 0.0, 0.5, 0.0);
    }
    catch(Exception &e)
    {
        cout << e << endl;
    }

    _apply_shader = true;

    */

    GLdouble u_min = -2.0, u_max = +2.0, v_min = -2.0, v_max = 2.0;

    GLdouble step_u = (u_max - u_min) / (4 - 1), step_v = (v_max - v_min) / 3;

    for (GLuint i = 0; i < 4; ++i)
    {
        GLdouble u = u_min + i * step_u;

        for (GLuint j = 0; j < 4; ++j)
        {
            GLdouble v = v_min + j * step_v;

            DCoordinate3 &ref = _patch(i, j);

            ref[0] = u;
            ref[1] = v;
            ref[2] = -2.0 + 4.0 * rand() / (GLdouble)RAND_MAX;
        }
    }

    try
    {
        if (!_patch.UpdateVertexBufferObjectsOfData())
            throw Exception("Could not update the VBO of the control net!");

        //ezt majd feluletrol kell valtoztatni
        _mesh = _patch.GenerateImage(50, 50);

        if (!_mesh)
        {
            // error
            throw "Mesh error";
        }

        if (!_mesh->UpdateVertexBufferObjects())
        {
            // error
            throw "VBO error";
        }
    }
    catch (Exception &e)
    {
        cout << e << endl;
    }
}

//-----------------------
// the rendering function
//-----------------------
void GLWidget::paintGL()
{
    // clears the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // stores/duplicates the original model view matrix
    glPushMatrix();

        // applying transformations
        glRotatef(_angle_x, 1.0, 0.0, 0.0);
        glRotatef(_angle_y, 0.0, 1.0, 0.0);
        glRotatef(_angle_z, 0.0, 0.0, 1.0);

        glTranslated(_trans_x, _trans_y, _trans_z);

        glScaled(_zoom, _zoom, _zoom);

        glDisable(GL_LIGHTING);

        glColor4f(0.8, 0.8, 0.8, 1.0);
        _patch.RenderData();

        glEnable(GL_LIGHTING);

        if (_mesh)
        {
            MatFBRuby.Apply();
            _mesh->Render();
        }



//        if ( _before_interpolation)
//        {
//            MatFBRuby.Apply() ;
//            _before_interpolation->Render();
//        }
//        if (_after_interpolation)
//        {

//                glEnable(GL_BLEND) ;
//                glDepthMask(GL_FALSE) ;
//                glBlendFunc(GL_SRC_ALPHA , GL_ONE ) ;
//                MatFBTurquoise.Apply() ;
//                _after_interpolation->Render();
//                glDepthMask(GL_TRUE ) ;
//                glDisable(GL_BLEND) ;
//         }

    /*
        // applying transformations
        glRotatef(_angle_x, 1.0, 0.0, 0.0);
        glRotatef(_angle_y, 0.0, 1.0, 0.0);
        glRotatef(_angle_z, 0.0, 0.0, 1.0);

        glTranslated(_trans_x, _trans_y, _trans_z);

        glScaled(_zoom, _zoom, _zoom);

        // render something
//        if (_apply_shader)
//        {
//            _shader.Enable();
//        }

        MatFBEmerald.Apply();
       // _shader.SetUniformVariable4f("mycolor", 0.5, 0.0, 0.5, 0.0);
        _mouse.Render();
//        _shader.Disable();

    // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
    // i.e., the original model view matrix is restored

        */
    glPopMatrix();



}
void GLWidget::_animate()
{
    GLfloat *vertex = _mouse.MapVertexBuffer(GL_READ_WRITE);
    GLfloat *normal = _mouse.MapNormalBuffer(GL_READ_ONLY);
    _angle += DEG_TO_RADIAN;
    if ( _angle >= TWO_PI)
        _angle -= TWO_PI;
    GLfloat scale = sin(_angle) / 3000.0;
    for ( GLuint i = 0; i < _mouse.VertexCount (); ++i )
    {
        for ( GLuint coordinate = 0; coordinate < 3; ++coordinate , ++vertex , ++normal )
            *vertex += scale * (*normal );
    }
    _mouse.UnmapVertexBuffer();
    _mouse.UnmapNormalBuffer();

    updateGL();
}
//----------------------------------------------------------------------------
// when the main window is resized one needs to redefine the projection matrix
//----------------------------------------------------------------------------
void GLWidget::resizeGL(int w, int h)
{
    // setting the new size of the rendering context
    glViewport(0, 0, w, h);

    // redefining the projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)w / (float)h;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // switching back to the model view matrix
    glMatrixMode(GL_MODELVIEW);

    updateGL();
}

//-----------------------------------
// implementation of the public slots
//-----------------------------------

void GLWidget::set_angle_x(int value)
{
    if (_angle_x != value)
    {
        _angle_x = value;
        updateGL();
    }
}

void GLWidget::set_angle_y(int value)
{
    if (_angle_y != value)
    {
        _angle_y = value;
        updateGL();
    }
}

void GLWidget::set_angle_z(int value)
{
    if (_angle_z != value)
    {
        _angle_z = value;
        updateGL();
    }
}

void GLWidget::set_zoom_factor(double value)
{
    if (_zoom != value)
    {
        _zoom = value;
        updateGL();
    }
}

void GLWidget::set_trans_x(double value)
{
    if (_trans_x != value)
    {
        _trans_x = value;
        updateGL();
    }
}

void GLWidget::set_trans_y(double value)
{
    if (_trans_y != value)
    {
        _trans_y = value;
        updateGL();
    }
}

void GLWidget::set_trans_z(double value)
{
    if (_trans_z != value)
    {
        _trans_z = value;
        updateGL();
    }
}

void GLWidget::setShaderStatus(bool value)
{
    if (_apply_shader != value)
    {
        _apply_shader = value;

        if (!_apply_shader)
        {
            _shader.Disable();
        }
        else
        {
            _shader.Enable();
        }

        updateGL();
    }
}

GLWidget::~GLWidget()
{
   if ( _before_interpolation)
       delete _before_interpolation, _before_interpolation = 0;
   if (_after_interpolation)
       delete _after_interpolation, _after_interpolation = 0;
}
